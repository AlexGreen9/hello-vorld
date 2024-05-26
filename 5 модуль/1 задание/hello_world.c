#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("My License the best");
MODULE_AUTHOR("Alex Grigoryeva");
MODULE_DESCRIPTION("My custom Hello World kernel module");

static int __init hello_init(void) {
    printk(KERN_INFO "Hello World! This is a custom kernel module by Alex Grigoryeva\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye World! Custom module under My License the best\n");
}
module_init(hello_init);
module_exit(hello_exit);
