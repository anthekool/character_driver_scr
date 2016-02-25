#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include "scull.h"
#include "header.h"
#include "declaration.h"

int ret,i;

//void unregister_chrdev_region(dev_t first,
//unsigned int count);
static void __exit exit_func(void)
{
	printk(KERN_INFO "BYE KERNAL\n");
	unregister_chrdev_region(dev[0].c_dev.dev,NO_OF_DEVICES);
	kfree(dev);
	for(i= 0;i<NO_OF_DEVICES;i++)
	cdev_del(&dev[i].c_dev);
	//if(ret == -1)
//	{

//		printk("error in unregister = %d\n",ret);
//	}

//	return 0;

}

module_exit(exit_func);
