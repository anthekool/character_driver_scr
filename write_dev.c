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
long could_not_copy,length_write=0;
//struct scull_qset *lqset;


ssize_t write_dev(struct file *fops, const char *buf, size_t count, loff_t *f_pos)
{
	struct scull_dev *ldev;
	char no_of_quantum;
	char rest_byte; 
	int counter;
	int llqset,llquantum;
	llqset = 16;//ldev->qset;
	llquantum = 4;///ldev->quantum;;
//	struct scull_qset *lqset;
//	struct scull_qset *lqset;
//	long could_not_copy;
	ldev = fops->private_data; 
//	ldev->qset = 16;
//	ldev->quantum = 4;
	rest_byte = count % llquantum;
	if(rest_byte)
	
		no_of_quantum = count /llquantum +1;
	else
		no_of_quantum = count /llquantum;

	printk(KERN_INFO "Present in write file\n");
	ldev->qset_struc = (struct scull_qset *)kmalloc(sizeof(struct scull_qset),GFP_KERNEL);
	ldev->qset_struc->data = (void **)kmalloc(sizeof(char *)*ldev->qset,GFP_KERNEL);
	memset(ldev->qset_struc->data,0,sizeof(char *)*ldev->qset);
	for(counter = 0;counter < no_of_quantum;counter++)
	{
		ldev->qset_struc->data[counter]= (void **)kmalloc(ldev->quantum,GFP_KERNEL);
		memset(ldev->qset_struc->data[counter],0,sizeof(ldev->quantum));
	///	ldev->qset_struc->data[1]= (void **)kmalloc(ldev->quantum,GFP_KERNEL);
		if((counter == no_of_quantum-1)&&(rest_byte))
		{
			
//			length_write = length_write -llquantum + rest_byte;	
			llquantum = rest_byte;

		}
		could_not_copy = copy_from_user(ldev->qset_struc->data[counter],&buf[length_write],llquantum);
			
		
		length_write = length_write - could_not_copy+llquantum;		
	}

	if(length_write == count)
	{
		printk(KERN_INFO "copy from user %ld \n",length_write);///(char *)(ldev->qset_struc->data[0]));////,could_not_copy);
	}

	printk(KERN_INFO "copy from user %ld \n",length_write);///(char *)(ldev->qset_struc->data[0]));////,could_not_copy);
	if(ldev->qset_struc->data != NULL)
	{
		printk(KERN_INFO "kmalloc successfully");
	}

	else
		printk(KERN_INFO "erro\n");

	return (length_write);


}
