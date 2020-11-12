#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include "rdmsr.h"

MODULE_LICENSE("GPL");

/* This function is executed on module load, i.e. when you run:

	$ sudo insmod kernel_rdmsr.ko
*/
static int __init rdmsr_init(void) {
	printk(KERN_INFO "Hello, kernel space!\n");
	return 0;
}

/* This function is executed on module unload, i.e. when you run
	$ sudo rmmod [-f] kernel_rdmsr
*/
static void __exit rdmsr_exit(void) {
	 printk(KERN_INFO "Goodbye, kernel space!\n");
}

module_init(rdmsr_init);
module_exit(rdmsr_exit);

