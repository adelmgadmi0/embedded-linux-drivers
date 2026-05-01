#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>

#define DEVICE_NAME "led_driver"
#define CLASS_NAME  "led"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Adel Mgadmi");
MODULE_DESCRIPTION("First LED Driver");

static int major;
static int led_state = 0;
static struct class *led_class;
static struct device *led_device;

static int led_open(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "device opened\n");
	return 0;
}

static ssize_t led_read (struct file *filep, char __user *buffer, size_t len, loff_t *offset){
	char state_msg [3];
	int state_msg_len;
	if (*offset > 0) return 0;
	state_msg_len = snprintf(state_msg, sizeof(state_msg), "%d\n", led_state);
	if(copy_to_user(buffer, state_msg, state_msg_len)) return -EFAULT;
	*offset += state_msg_len;
	return state_msg_len;
}

static ssize_t led_write (struct file *filep, const char __user *buffer, size_t len, loff_t *offset){

	char inbuf[3] = {0};
	if (copy_from_user(inbuf, buffer, len)) return -EFAULT;
	if (inbuf[0] == '1') {
		led_state = 1;
		printk(KERN_INFO "LED Turned On.\n");
	}
	else if (inbuf[0] == '0'){
		led_state = 0;
		printk(KERN_INFO "LED Turned Off.\n");
	}
	return len;

}

static int led_release(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "device closed\n");
	return 0;
}

static struct file_operations fops = {
	.owner          = THIS_MODULE,
	.open           = led_open,
	.read		= led_read,
	.write          = led_write,
	.release        = led_release,

};

static char *led_devnode (const struct device *dev, umode_t *mode)
{
	if (mode) *mode = 0666;
	return NULL;
}

static int __init led_init(void)
{
        major = register_chrdev(0, "led_driver", &fops);
	led_class = class_create(CLASS_NAME);
	led_class->devnode = led_devnode;
	led_device = device_create(led_class, NULL, MKDEV(major,0), NULL, DEVICE_NAME);
	printk(KERN_INFO "Driver loaded, major = %d\n", major);	
        return 0;
}

static void __exit led_exit(void)
{
	device_destroy(led_class, MKDEV(major,0));
	class_destroy(led_class);
        unregister_chrdev(major, "led_driver");
	printk(KERN_INFO "Driver Unloaded\n");
}


module_init(led_init);
module_exit(led_exit);
