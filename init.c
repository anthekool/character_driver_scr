#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include "scull.h"
#include "header.h"
#include "declaration.h"

int open_dev(struct inode *,struct file *);
int close_dev(struct inode *,struct file *);
int scull_trim(struct scull_dev *);
struct scull_dev *dev,*ldev;
dev_t devno;
/*struct file_operations foper = 
{
	open : open_dev,
	release : close_dev	

};*/
//struct file_operations foper;

//struct scull_dev *dev;
int registr,major_no,minor_no,err,no_of_nodes;
//dev_t devno;
//
static int __init tnit_func(void)
{



	printk(KERN_INFO "HI KERNAL\n");
	registr = alloc_chrdev_region(&devno,0,NO_OF_DEVICES, "anupam_device");
	major_no = MAJOR(devno);
	minor_no = MINOR(devno);
	if(registr == -1)
	{

		MSG("can't register device with kernel\n");
		return registr;
	}
	else
	{

		MSG("device registered with major and minor no is %d %d\n" , major_no,minor_no);


	}

	
//	devno = MKDEV(major_no,minor_no + no_of_nodes);
	dev  = kmalloc(NO_OF_DEVICES*sizeof(struct scull_dev),GFP_KERNEL);
	memset(dev,0,NO_OF_DEVICES*sizeof(struct scull_dev));

	for(no_of_nodes=0;no_of_nodes < 5;no_of_nodes++)
	{

		dev[no_of_nodes].quantum 	= 4;
		dev[no_of_nodes].qset 		= 4;
		dev->size 	= 16;
		devno = MKDEV(major_no,minor_no + no_of_nodes);
//		dev[no_of_nodes] = (struct scull_dev *)kmalloc(1*sizeof(struct scull_dev),GFP_KERNEL);
//		memset((char *)dev[no_of_nodes],0,sizeof(struct scull_dev));
		cdev_init(&dev[no_of_nodes].c_dev, &foper);
		
		dev[no_of_nodes].qset_struc = kmalloc(sizeof(struct scull_qset),GFP_KERNEL);
		dev[no_of_nodes].c_dev.owner = THIS_MODULE;
        	dev[no_of_nodes].c_dev.ops = &foper;
    		err = cdev_add (&dev[no_of_nodes].c_dev, devno, 1);
    		/* Fail gracefully if need be */
    		if (!err)
    			printk(KERN_NOTICE "inserted in kernal succesafully");
		else
			printk(KERN_NOTICE "Error in kernal insertion");

	}


	for(no_of_nodes=0;no_of_nodes < 5;no_of_nodes++)
	{

	MSG("Minor numbers are %d",MINOR(dev[no_of_nodes].c_dev.dev));

	}

	return 0;

}


	module_init(tnit_func);

