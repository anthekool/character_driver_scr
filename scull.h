
#include "header.h"
#include "declaration.h"
#include <linux/fs.h>
#include <linux/cdev.h>
struct scull_qset {
   void **data;
   struct scull_qset *next;
};

struct scull_dev {
    struct scull_qset *qset_struc;  	/* Pointer to first quantum set */
    int quantum;              	/* the current quantum size */
    int qset;                 	/* the current array size */
    unsigned long size;       	/* amount of data stored here */
    unsigned int access_key;  	/* used by sculluid and scullpriv */
    struct semaphore sem;     	/* mutual exclusion semaphore     */
    struct cdev c_dev;     	/* Char device structure      */
};

//extern int open_dev(struct inode *,struct file *);
//extern int close_dev(struct inode *,struct file *);
extern struct file_operations foper;
extern struct scull_qset *lqset;
extern struct scull_dev *dev,*ldev;
extern struct cdev c_dev;
extern dev_t devno;
//extern struct file_operations foper;
