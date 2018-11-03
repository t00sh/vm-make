vm-make : build small QEMU images using Busybox.

--------------------------

Folders :

- **linux** : Linux Kernel configuration

- **busybox** : Busybox configuration

- **initramfs** : Filesystem

- **module** : source of Linux Kernel Module

- **build** : final machine


To build the VM :

``` shell
make
```

To execute the VM :

``` shell
cd ./build && ./start.sh
```
