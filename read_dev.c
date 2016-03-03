#include "scull.h"
#include "header.h"
#include "declaration.h"
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

extern ssize_t  read_dev(struct file *,char *, size_t , loff_t *);
long could_read_not_copy,final_nof_byte=0,length_write =0;
//struct scull_qset *lqset;
//int rest_byte1;

ssize_t read_dev(struct file *fops, char *buf, size_t count, loff_t *f_pos)
{


	struct scull_dev *ldev;
	int no_of_quantum,llquantum;//,j;
	int counter,llqset,datasize,j =0;
	long no_of_byte=0,g_count;
	
	int no_qset_struc;

	g_count = count;
	ldev = fops->private_data;
 
	llqset = ldev->qset;
	llquantum = ldev->quantum;
	datasize = llqset*llquantum;
	/*no of qset item*/
	no_qset_struc = count/datasize;
	if(count%datasize)
	no_qset_struc++;

	/*no of quantum*/
	no_of_quantum = count/llquantum;
	if(count % llquantum)
	no_of_quantum++;
	

	if(!ldev->qset_struc)

	{
		printk(KERN_INFO "error in allocating reading file\n");

	}
//	ldev->qset_struc = (struct scull_qset *)kmalloc(sizeof(struct scull_qset),GFP_KERNEL);
//	lqset->data = (void **)kmalloc(sizeof(char *)*ldev->qset,GFP_KERNEL);
//	memset(lqset->data,0,sizeof(char *)*ldev->qset);
//	lqset->data[0]= (void **)kmalloc(ldev->quantum,GFP_KERNEL);
	
	j = 0;

	printk(KERN_INFO "no of qset structure %d\n",no_qset_struc);

	for(counter =0;counter < no_of_quantum; counter++)
	{


		if(g_count < llquantum)
		llquantum = g_count; 

		could_read_not_copy = copy_to_user(&buf[no_of_byte],ldev->qset_struc->data[j],llquantum);

		no_of_byte = no_of_byte + llquantum - could_read_not_copy;
		g_count = g_count - llquantum;
		printk(KERN_INFO "no of byte value %ld %ld %d %s\n",no_of_byte,could_read_not_copy,counter,(char *)ldev->qset_struc->data[j]);

		if((j == ldev->qset-1)&&(no_qset_struc > 1))
		{
			j = 0;			
			ldev->qset_struc = ldev->qset_struc->next;
			if(!ldev->qset_struc)
			{
				printk(KERN_INFO "error in next location\n");
				return 0;
			}
		//no_of_quantum = llqset;
		}


		else
		j++;


	}




	//if(no_of_byte == count)
	//{
		printk(KERN_INFO "copy from read user %s %ld %d %ld %ld%d%d\n",buf,length_write,no_of_quantum,g_count,no_of_byte,ldev->quantum,ldev->qset);
//	}


//	if(lqset->data != NULL)
//	{
//		printk(KERN_INFO "kmalloc successfully");
//	}

//	else
		printk(KERN_INFO "read string %s\n",buf);

	return (no_of_byte);


}
