Kernel Linked List implentation

kernel_linked_list is a linux kernel module that demonstrates linked list data structure and its APIs.
You can find the implementations of linked list APIs in "include/linux/list.h" from kernel source tree.


Usage:
$ make
$ sudo insmod kernel_linklist.ko 
$ dmesg
$ sudo rmmod kernel_linklist.ko
