#!/usr/bin/env bash

# ./bin/qmk-cli.sh c2json -kb splitkb/halcyon/kyria/rev4 -km default > ./keymap-drawings/kyria.json
# uvx --from keymap-drawer keymap parse -c 14 -q ./keymap-drawings/kyria.json > ./keymap-drawings/kyria.yaml
uvx --from keymap-drawer keymap draw ./keymap-drawings/kyria.yaml > ./keymap-drawings/kyria.svg

./bin/qmk-cli.sh c2json keyboards/silakka54/keymaps/default/keymap.c > ./keymap-drawings/silakka.json
uvx --from keymap-drawer keymap parse -c 14 -q ./keymap-drawings/silakka.json > ./keymap-drawings/silakka.yaml
uvx --from keymap-drawer keymap draw ./keymap-drawings/silakka.yaml > ./keymap-drawings/silakka.svg
