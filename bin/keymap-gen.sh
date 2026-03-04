#!/usr/bin/env bash

./bin/qmk-cli.sh c2json -kb splitkb/halcyon/kyria/rev4 -km default > ./keymap-drawings/kyria.json
uvx --from keymap-drawer keymap parse -c 14 -q ./keymap-drawings/kyria.json > ./keymap-drawings/kyria.yaml
uv run ./keymap-drawings/kyria.py
uvx --from keymap-drawer keymap -c ./keymap-drawings/keymap-drawer.config.yaml draw ./keymap-drawings/kyria.yaml > ./keymap-drawings/kyria.svg

./bin/qmk-cli.sh c2json keyboards/silakka54/keymaps/default/keymap.c > ./keymap-drawings/silakka.json
uvx --from keymap-drawer keymap parse -c 14 -q ./keymap-drawings/silakka.json > ./keymap-drawings/silakka.yaml
uvx --from keymap-drawer keymap -c ./keymap-drawings/keymap-drawer.config.yaml draw ./keymap-drawings/silakka.yaml > ./keymap-drawings/silakka.svg

uvx --from keymap-drawer keymap parse -c 14 -z ./lotus58/config/lotus58.keymap > ./keymap-drawings/lotus58.yml
uvx --from keymap-drawer keymap draw ./keymap-drawings/lotus58.yml > ./keymap-drawings/lotus58.svg
