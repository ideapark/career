/*
 * hello.c - Demonstrates module documentation.
 */
#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h>   /* Needed for the macros */

#define DRIVER_AUTHOR "Peter Jay Salzman <p@dirac.org>"
#define DRIVER_DESC   "A simple driver"

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello world.\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodby world.\n");
}

module_init(hello_init);
module_exit(hello_exit);

/*
 * You can use strings, like this:
 */

/*
 * Get rid of taint message by declaring code as GPL.
 */
MODULE_LICENSE("CPL");

/*
 * Or with defines, like this:
 */
MODULE_AUTHOR(DRIVER_AUTHOR); /* Who wrote this module? */
MODULE_DESCRIPTION(DRIVER_DESC); /* What does this module do */

/*
 * This module uses /dev/testdevice. The MODULE_SUPPORTED_DEVICE
 * macro might be used in the future to help automatic configuration
 * of modules, but is currently unused other than for documentation
 * purpose.
 */
MODULE_SUPPORTED_DEVICE("testdevice");
