#!/usr/bin/env bash

DIR=$(dirname "$(realpath $0)")
export QMK_USERSPACE="${DIR}/out"
export SKIP_FLASHING_SUPPORT=1

cd qmk_firmware
util/docker_build.sh silakka54:default
cd -
