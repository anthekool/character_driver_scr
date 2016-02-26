#include "scull.h"
#include "header.h"
#include "declaration.h"
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

extern ssize_t  write_dev(struct file *, const char *, size_t , loff_t *);
long could_not_copy;
//struct scull_qset *lqset;


ssize_t write_dev(struct file *fops, const char *buf, size_t count, loff_t *f_pos)
{
	struct scull_dev *ldev;
//	ldev->qset = 16;
//	ldev->quantum = 4;
//	struct scull_qset *lqset;
//	struct scull_qset *lqset;
//	long could_not_copy;
	ldev = fops->private_data; 
//	ldev->qset = 16;
//	ldev->quantum = 4;

	printk(KERN_INFO "Present in write file\n");
	ldev->qset_struc = (struct scull_qset *)kmalloc(sizeof(struct scull_qset),GFP_KERNEL);
	ldev->qset_struc->data = (void **)kmalloc(sizeof(char *)*ldev->qset,GFP_KERNEL);
	memset(ldev->qset_struc->data,0,sizeof(char *)*ldev->qset);
	ldev->qset_struc->data[0]= (void **)kmalloc(ldev->quantum,GFP_KERNEL);
	could_not_copy = copy_from_user(ldev->qset_struc->data[0],buf,4);

	if(could_not_copy == 0)
	{
		printk(KERN_INFO "copy from user %ld \n",could_not_copy);///(char *)(ldev->qset_struc->data[0]));////,could_not_copy);
	}

	if(ldev->qset_struc->data != NULL)
	{
		printk(KERN_INFO "kmalloc successfully");
	}

	else
		printk(KERN_INFO "erro\n");

	return (4-could_not_copy);


}
