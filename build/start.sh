#!/bin/sh

qemu-system-x86_64 \
    -kernel ./bzImage \
    -initrd ./initramfs.cpio.gz  \
    -machine pc,accel=kvm \
    -append 'console=ttyS0 loglevel=3 oops=panic panic=1' \
    -nographic \
    -no-reboot
