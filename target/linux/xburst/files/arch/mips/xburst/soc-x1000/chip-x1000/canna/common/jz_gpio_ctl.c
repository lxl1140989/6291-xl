#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/gpio.h>
#include <linux/proc_fs.h>
#include <linux/syscore_ops.h>
#include <linux/delay.h>
#include <irq.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/version.h>

#include <gpio.h>
#include <soc/gpio.h>


#define RESET_BTN		GPIO_PC(23)
#define DEC_BTN			GPIO_PC(22)

#define BTN_PRESS		0
#define BTN_RELEASE		1

#define GET_RESET_BTN			0x30
#define GET_DEC_BTN				0x31

// static unsigned int cmd=0;

static int jz_gpio_init(void)
{

	gpio_request(RESET_BTN, "reset button");
	gpio_direction_input(RESET_BTN);
	
	gpio_request(DEC_BTN, "umount button");
	gpio_direction_input(DEC_BTN);

	return 0;
}


static long jz_gpio_ioctl(struct file *file, unsigned int action,unsigned long arg)
{
	unsigned char btn_status = 0 ;
	unsigned int cmd=0;

	cmd = action;
		
	switch (cmd) {
		case GET_RESET_BTN:
			btn_status=__gpio_get_value(RESET_BTN);
			//printk("reset btn status = %d\n", btn_status);
			if (copy_to_user((void __user *)arg,&btn_status, sizeof(btn_status)))
				return -EFAULT;
			break;
		
		case GET_DEC_BTN:
			btn_status=__gpio_get_value(DEC_BTN);
			//printk("dec btn status = %d\n", btn_status);
			if (copy_to_user((void __user *)arg,&btn_status, sizeof(btn_status)))
				return -EFAULT;
			break;

		
		default:
			
			printk("Not supported action!\n");
			break;	
	}
	return 0;

}
static int jz_gpio_open(struct inode *inode, struct file *file)
{
//	printk("proc_encryp_open\n\n");
	return 0;
}
#if 0
static int jz_gpio_read(struct inode *inode, struct file *file)
{
//	printk("proc_encryp_open\n\n");
	return 0;
}
static int jz_gpio_write(struct inode *inode, struct file *file)
{
//	printk("proc_encryp_open\n\n");
	return 0;
}
#endif
static struct file_operations gpio_ctl_fops = { 
	open:jz_gpio_open,
	read:NULL, 
	write:NULL,
	unlocked_ioctl:jz_gpio_ioctl, 
}; 


static int __init jz_gpio_init_proc(void)
{
	struct proc_dir_entry *res=NULL;
	jz_gpio_init();

	res = create_proc_entry("jz_gpio", 0, NULL);
	if (res) {
		res->proc_fops = &gpio_ctl_fops;
	}

	return 0;
}

module_init(jz_gpio_init_proc);
