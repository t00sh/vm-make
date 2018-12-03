#!/bin/sh

# Create mount point if needed
mkdir -p mountpoint/

# Running QEMU
qemu-system-i386 \
    -enable-kvm \
    -kernel ./bzImage \
    -initrd ./initramfs.cpio.gz  \
    -append 'console=ttyS0 loglevel=3 oops=panic panic=1' \
    -fsdev local,id=exp1,path=./mountpoint,security_model=mapped \
    -device virtio-9p-pci,fsdev=exp1,mount_tag=mountpoint \
    -no-reboot \
    -nographic
