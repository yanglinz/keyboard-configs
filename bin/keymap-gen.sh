#!/usr/bin/env bash

./bin/qmk-cli.sh c2json keyboards/silakka54/keymaps/default/keymap.c > ./keymap-drawings/silakka54.json

# uvx --from keymap-drawer keymap parse -c 14 -q ./keymap-drawings/silakka54.json
# uvx --from keymap-drawer keymap draw ./image/lotus58.yml > image/lotus58.svg
