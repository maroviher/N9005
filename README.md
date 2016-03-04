### Ahmed kernel for N9005 (Note 3 Quallcomm SoC) based on Samsung stock N9005XXUGBOJ1(Lollipop)
		Changes:
		* SELinux possible set to permissive
		
		Removed (nobody needs it in daily use):
		* CONFIG_DEBUG_USER (annoying illegal instruction messages in dmesg)
		* CONFIG_MSM_RTB
		* CONFIG_SEC_PM_DEBUG
		* CONFIG_DEBUG_INFO
		* printk configurable (default off)
		* android logger
		* CONFIG_SEC_MISC
		* CONFIG_SEC_DEBUG
		* CONFIG_SEC_DEBUG_SUBSYSCONFIG_SEC_DEBUG_SCHED_LOG

### Original source code: http://opensource.samsung.com/reception/receptionSub.do?method=sub&sub=F&searchValue=n9005
		Versions:

				N9005XXUGBOB6 SM-N9005_EUR_LL_Opensource_Update2.zip 25 February 2015
				N9005XXUGBOA5 SM-N9005_EUR_LL_Opensource_Update1.zip 20 January 2015
				N9005XXUGBOF1 SM-N9005_EUR_LL_Opensource.zip         11 June 2015
				N9005XXUGBOJ1 SM-N9005_EUR_LL_Opensource.zip         19 November 2015 <<<<<<<<<<<<<
				
### How to compile:
				#if you want original samsung configs than replace ahmed_msm8974_sec_defconfig through msm8974_sec_defconfig in build_kernel.sh
				git clone https://github.com/maroviher/N9005
				cd N9005/N9005XXUGBOJ1/linux_kernel
				./build_kernel.sh
				#Odin flashable TAR is in the folder 'boot_image'
				#WiFi will not work. To fix: modify build.prop ro.securestorage.support=true - Change to false and reboot
