vm-make : build small QEMU images using Busybox.

--------------------------

vm-make is a set of makefiles to build minimal QEMU virtual machines. It uses Busybox as a main toolbox.

# "linux" folder

The **linux** folder contains the Linux Kernel configuration (__linux/config__) configured for x86-64 systems. You can use your own configuration file : you only have to replace the __linux/config__ file.

# "busybox" folder

The **busybox** folder contains the Busybox configuration (__busybox/config__). You can use your own configuration : you only have to replace this file with your own.

# "module" folder

The **module** folder is a base of a small Linux Kernel Module. You can replace it with your own source code.

__Note__ : this folder depends on **linux** folder (you must compile it first).

# "initramfs" folder

The **initramfs** is the base system of your virtual machine. You can add/edit files in **initramfs/fs** to customize your VM.

__Note__ : this folder depends on **linux**, **busybox** and **module** folders.

# "build" folder

This folder contains the files to run the final virtual machine. You can edit the **build/start.sh** script to use your own QEMU options.

__Note__ : this folder depends on **linux** and **initramfs** folders.


# Building the VM

To build the VM, edit the **Makefile.inc** configuration file, edit configurations and filesystem (see previous sections) and run :

``` shell
make
```

# Executing the VM

To execute the VM just run :

``` shell
cd ./build && ./start.sh
```
