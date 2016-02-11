### Lollipop Kernel for N9005 (Note 3) based on N9005XXUGBOJ1 with Quallcomm SoC
		Changes:
		* SELinux possible set to permissive
		* CONFIG_DEBUG_USER=n (annoying illegal instruction messages in dmesg)

### Original source code: http://opensource.samsung.com/reception/receptionSub.do?method=sub&sub=F&searchValue=n9005
		Versions:

				N9005XXUGBOB6 SM-N9005_EUR_LL_Opensource_Update2.zip 25 February 2015
				N9005XXUGBOA5 SM-N9005_EUR_LL_Opensource_Update1.zip 20 January 2015
				N9005XXUGBOF1 SM-N9005_EUR_LL_Opensource.zip         11 June 2015
				N9005XXUGBOJ1 SM-N9005_EUR_LL_Opensource.zip         19 November 2015 <<<<<<<<<<<<<
				
### How to compile:
				git clone https://github.com/maroviher/N9005
				cd N9005/N9005XXUGBOJ1/linux_kernel
				./build_kernel.sh
				Odin flashable TAR is in the folder 'boot_image'
				WiFi not working. To fix: modify build.prop ro.securestorage.support=true - Change to false. WiFi works on reboot

### Setting up NFS4 client on Note 3:
	On Server:
		echo 262144 > /proc/fs/nfsd/max_block_size
		systemctl start nfs-server
	In N9005:
		su -mm
		mount.nfs4 192.168.222.1:/ /storage/UsbDriveA -o vers=4,nolock,rsize=262144,wsize=262144
