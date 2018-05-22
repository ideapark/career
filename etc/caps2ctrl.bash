#!/us/bin/env bash

# NOTE: root permission required to run this script

(
    cat <<EOF
keymaps 0-2,4-6,8-9,12
keycode 58 = Control
EOF
) | tee /usr/share/kbd/keymaps/caps2ctrl.map

localectl set-keymap --no-convert caps2ctrl.map
