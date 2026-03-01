#!/usr/bin/env bash

ROOT_DIR="$(dirname "$(realpath $0)")/.."

docker run --rm \
  -w /qmk_firmware \
  -v "${ROOT_DIR}/qmk_firmware:/qmk_firmware:z" \
  -v "${ROOT_DIR}/out:/qmk_userspace:z" \
  -e QMK_USERSPACE=/qmk_userspace \
  -e SKIP_GIT= -e SKIP_VERSION= -e MAKEFLAGS= \
  ghcr.io/qmk/qmk_cli qmk "$@"
