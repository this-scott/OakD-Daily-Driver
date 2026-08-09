#!/usr/bin/env bash
set -euo pipefail


APP_NAME="OakD-Daily"
BRIDGE_BIN="Oak-Bridge"
PREFIX="/usr/local/"
BUILD_DIR="build"


echo "==> Checking v4l2loopback"
if ! modinfo v4l2loopback &>/dev/null; then
    echo "==> Installing v4l2loopback (dkms + ctl utility)"
    if command -v apt &>/dev/null; then
        sudo apt update && sudo apt install -y v4l2loopback-dkms v4l2loopback-utils
    elif command -v dnf &>/dev/null; then
        sudo dnf install -y v4l2loopback v4l2loopback-utils
    elif command -v pacman &>/dev/null; then
        sudo pacman -S --noconfirm v4l2loopback-dkms
    else
        echo "Install v4l2loopback-dkms manually for your distro, then re-run this script." >&2
        exit 1
    fi
fi


echo "==> Persisting module config"
echo "v4l2loopback" | sudo tee /etc/modules-load.d/${APP_NAME}.conf >/dev/null
sudo tee /etc/modprobe.d/${APP_NAME}.conf >/dev/null <<EOF
options v4l2loopback devices=0 exclusive_caps=1
EOF
sudo modprobe v4l2loopback


echo "==> Installing systemd service"
sudo tee /etc/systemd/system/${APP_NAME}.service >/dev/null <<EOF
[Unit]
Description=MyriadX virtual camera bridge

[Service]
Type=simple #TODO: Wrap ExecStart into a bootscript
ExecStartPre=/usr/bin/v4l2loopback-ctl add -n "MyriadX Cam" /dev/video10
ExecStart=${PREFIX}/bin/${BRIDGE_BIN}
ExecStopPost=/usr/bin/v4l2loopback-ctl delete /dev/video10
EOF


echo "==> Building bridge"
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR" --parallel


echo "==> Installing hotplug dispatch script"
sudo tee /usr/local/bin/myriadx-cam-hotplug.sh >/dev/null <<'EOF'
#!/usr/bin/env bash
case "$1" in
    add)    systemctl --no-block start myriadx-cam.service ;;
    remove) systemctl --no-block stop  myriadx-cam.service ;;
esac
EOF
sudo chmod +x /usr/local/bin/myriadx-cam-hotplug.sh


echo "==> Installing udev rule"
sudo tee /etc/udev/rules.d/99-${APP_NAME}.rules >/dev/null <<'EOF'
ACTION=="add",    SUBSYSTEM=="usb", ATTR{idVendor}=="03e7", ATTR{idProduct}=="2485", RUN+="/usr/local/bin/myriadx-cam-hotplug.sh add"
ACTION=="remove", SUBSYSTEM=="usb", ATTR{idVendor}=="03e7", ATTR{idProduct}=="2485", RUN+="/usr/local/bin/myriadx-cam-hotplug.sh remove"
EOF

echo "==> Reloading udev and systemd"
sudo udevadm control --reload-rules
sudo udevadm trigger
sudo systemctl daemon-reload

echo "==> Done. Plug in the Myriad X — /dev/video10 should appear automatically."
