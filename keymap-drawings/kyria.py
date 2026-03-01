# /// script
# dependencies = [
#   "PyYAML",
# ]
# ///

from pathlib import Path

import yaml


def post_process(kyria_data):
    kyria_data["layout"]["layout_name"] = "LAYOUT_split_3x6_5"
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
