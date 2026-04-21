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
static int led_open(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "device opened\n");
    return 0;
}


static int led_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "device closed\n");
    return 0;
}

static struct file_operations fops = {
    .owner          = THIS_MODULE,
    .open           = led_open,
    .release        = led_release,

};
static int __init led_init(void)
{
     major = register_chrdev(0, "led_driver", &fops);
     printk(KERN_INFO "Driver loaded, major = %d\n", major);
     return 0;
}

static void __exit led_exit(void)
{
     unregister_chrdev(major, "led_driver");
}

module_init(led_init);
module_exit(led_exit);
