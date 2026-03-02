# /// script
# dependencies = [
#   "PyYAML",
# ]
# ///

from pathlib import Path

import yaml


SHIFT_CHAR_MAP = {
    "Sft+1": "!",
    "Sft+2": "@",
    "Sft+3": "#",
    "Sft+4": "$",
    "Sft+5": "%",
    "Sft+6": "^",
    "Sft+7": "&",
    "Sft+8": "*",
    "Sft+9": "(",
    "Sft+0": ")",
    "Sft+-": "_",
    "Sft+=": "+",
    "Sft+[": "{",
    "Sft+]": "}",
    "Sft+;": ":",
    "Sft+'": '"',
    "Sft+,": "<",
    "Sft+.": ">",
    "Sft+/": "?",
    "Sft+`": "~",
    "Sft+\\": "|",
}


def replace_shifted_chars(value):
    """Recursively replace shifted character combinations with their actual characters."""
    if isinstance(value, str):
        for shift_combo, char in SHIFT_CHAR_MAP.items():
            value = value.replace(shift_combo, char)
        return value
    elif isinstance(value, dict):
        return {k: replace_shifted_chars(v) for k, v in value.items()}
    elif isinstance(value, list):
        return [replace_shifted_chars(item) for item in value]
    return value


def post_process(kyria_data):
    kyria_data["layout"]["layout_name"] = "LAYOUT_split_3x6_5"
    
    # Replace shifted character combinations in all layers
    if "layers" in kyria_data:
        kyria_data["layers"] = replace_shifted_chars(kyria_data["layers"])
    
    return kyria_data


def main():
    current_file_path = Path(__file__)
    yaml_path = (current_file_path / "../kyria.yaml").resolve()

    data = None
    # 1. Load the existing YAML data
    with open(yaml_path, "r") as file:
        # Use yaml.safe_load() for security to prevent arbitrary Python object creation
        data = yaml.safe_load(file)
        data = post_process(data)

        # 3. Write the modified data back to the file
    with open(yaml_path, "w") as file:
        # Use sort_keys=False to preserve the order of keys as much as possible
        # Use default_flow_style=False for block style formatting
        yaml.dump(data, file, sort_keys=False, default_flow_style=False)


if __name__ == "__main__":
    main()
