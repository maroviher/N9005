#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/input.h>
#include <linux/hid.h>

//void inp_evt_set_hook_fn(int (*p_fn_inp_evt_hook_fn)(struct input_dev *dev, struct input_handle *handle, unsigned int type, unsigned int code, int value));
//void inp_evt_set_hook_fn1(int (*p_fn_inp_evt_hook_fn1)(struct hid_device *hdev, const char * str));
int32_t ahmed_focus_control(uint16_t ui1);
static char strProcPath[] = "ahmed_focus";
void lock_msm_actuator_set_position(bool bLock);
static char *ahm_buf;
size_t buf_size = 1024;
size_t buf_data_available = 0;
extern bool bDisablePrintk;

static int ahmed_focus_proc_write(struct file *sp_file,const char __user *buf, size_t size, loff_t *offset)
{
	int i2, i3;
	int len = size;
	if(0 == memcmp(buf, "lock\n", min(size, (size_t)5)))
	{
		lock_msm_actuator_set_position(true);
		return len;
	}
	else
	{
		if(0 == memcmp(buf, "unlock\n", min(size, (size_t)7)))
		{
			lock_msm_actuator_set_position(false);
			return len;
		}
	}
	if (sscanf(buf, "%i %i", &i2, &i3) != 2)
		return -EINVAL;
	//my_printk("%d %d\n", i2, i3);
	ahmed_focus_control(i2);
	return len;
}

static int charge_proc_read(struct seq_file *m, void *v)
{/*
	if(count < buf_data_available)
		return -ENXIO;
	if(111 == copy_to_user(buf, ahm_buf, buf_data_available))
		buf_data_available = 0;
	buf_data_available = 0;
	return count;*/
	char str[522];
	int iLen = snprintf(str, sizeof(str), "%d-%s", buf_data_available, ahm_buf);
	seq_printf(m, "%s\n", str);
	return 0;
}

static int focus_open_callback(struct inode *inode, struct file *file){
        return single_open(file, charge_proc_read, NULL);
}

static const struct file_operations charge_proc_fops = {
        .owner = THIS_MODULE,
		.open = focus_open_callback,
        .write = ahmed_focus_proc_write,
		.read = seq_read,
};

/*
#define ahm_focus_max 511
#define ahm_focus_min 1
static void* pMouseDrvData = NULL;
static struct work_struct focus_work;
static int usAhmFocus = 100;
static int iStep=10;

int  fn_inp_evt_hook_fn(struct input_dev *dev, struct input_handle *handle, unsigned int type, unsigned int code, int value)
{
	if(pMouseDrvData == input_get_drvdata(dev))//connected mouse
	{
		if ((BTN_RIGHT == code) && (EV_KEY == type))
		{
			if(value == 1)//right button clicked
				iStep = 1;
			else if(value == 0)//right button released
				iStep = 10;
			return 123;
		}
		if ((REL_WHEEL == code) && (EV_REL == type))
		{
			if(value == 1)//wheel up
			{
				usAhmFocus+=iStep;
				if(usAhmFocus > ahm_focus_max)
					usAhmFocus = ahm_focus_max;
			}
			else if(value == -1)//wheel down
			{
				usAhmFocus-=iStep;
				if(usAhmFocus < ahm_focus_min)
					usAhmFocus = ahm_focus_min;
			}
			schedule_work(&focus_work);
			return 123;
		}
	}
    return 0;
}

int  fn_inp_evt_hook_fn1(struct hid_device *hdev, const char * str)
{
	char str_mouse[] = "Mouse";
	if(0 == memcmp(str, str_mouse, sizeof(str_mouse)))
			pMouseDrvData=hdev;
	return 0;
}

static void focus_func(struct work_struct *work)
{
	ahmed_focus_control(usAhmFocus, 4000);
}*/

static int __init ahmed_focus_init_module(void)
{
	//inp_evt_set_hook_fn(fn_inp_evt_hook_fn);
	//inp_evt_set_hook_fn1(fn_inp_evt_hook_fn1);

	if (!proc_create(strProcPath, 0644, NULL, &charge_proc_fops)) {
		printk(KERN_ERR "couldn't create %s\n", strProcPath);
		return -EINVAL;
	}

	ahm_buf = kmalloc(buf_size, GFP_KERNEL);
	if (!ahm_buf)
		return -ENOMEM;

	//INIT_WORK(&focus_work, focus_func);

	return 0;
}

static void __exit ahmed_focus_exit_module(void)
{
	kfree(ahm_buf);
	//inp_evt_set_hook_fn(NULL);
	remove_proc_entry(strProcPath, NULL);
}

module_init(ahmed_focus_init_module);
module_exit(ahmed_focus_exit_module);
MODULE_DESCRIPTION("Ahmed focus driver");
MODULE_LICENSE("GPL v2");
