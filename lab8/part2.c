#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>
#include <asm/param.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	printk(KERN_INFO "%lu\n", GOLDEN_RATIO_PRIME);
	printk(KERN_INFO "slu jiffies and slu Hz\n", jiffies, HZ);
	return0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk( KERN_INFO "Removing Module\n" );
	printk( KERN_INFO "glu\n", gcd (3300,24)) ;
	printk( KERN_INFO "glu jiffies\n", jiffies);
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE ( "GPL" );
MODULE_DESCRIPTION( "Simple Module");
MODULE_AUTHOR "SGG" );