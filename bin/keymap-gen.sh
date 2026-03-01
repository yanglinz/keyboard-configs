#!/usr/bin/env bash

./bin/qmk-cli.sh c2json keyboards/silakka54/keymaps/default/keymap.c
# uvx --from keymap-drawer keymap parse -c 14 -q ./silakka54/keyboard.json > ./image/silakka54.yml
# uvx --from keymap-drawer keymap draw ./image/lotus58.yml > image/lotus58.svg
