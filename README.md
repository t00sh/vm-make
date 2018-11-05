vm-make : build small QEMU images using Busybox.

--------------------------

vm-make is a set of makefiles to build minimal QEMU virtual machines. It uses Busybox as a main toolbox.

There is a set of VM templates in **templates** directory. For example, to build a VM from the **./templates/x86_64** template, edit as you need all files in this folder and then, run :

``` shell
make CONF_TEMPLATE=./templates/x86_64/
```

To execute the VM just run :

``` shell
cd ./build && ./start.sh
```
