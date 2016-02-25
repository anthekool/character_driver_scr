#define DEBUG
#ifdef DEBUG
#define MSG(string, args...) printk(KERN_DEBUG "schar:" string, ##args)
#else
#define MSG(string, args...)
#endif




#define SCULL_QUANTUM 		16
#define SCULL_QUANTUM_QSET	64
#define SIZE			128
#define NO_OF_DEVICES           5	 
