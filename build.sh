#!/usr/bin/env bash

DIR=$(dirname "$(realpath $0)")
export QMK_USERSPACE="${DIR}/out"
export SKIP_FLASHING_SUPPORT=1

function copy_source() {
  rm -rf qmk_firmware/keyboards/silakka54
  cp -r silakka54 qmk_firmware/keyboards/
}

function compile() {
  cd qmk_firmware
  util/docker_build.sh silakka54:default
  cd -
}

copy_source
compile
