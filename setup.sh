QMK_FIRMWARE_REF="0.31.9"

function setup_qmk_repo() {
  git clone git@github.com:qmk/qmk_firmware.git
  cd qmk_firmware
  git checkout $QMK_FIRMWARE_REF
  cd -
}

setup_qmk_repo
