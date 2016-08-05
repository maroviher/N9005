#!/bin/bash

export ARCH=arm
#export CROSS_COMPILE=/opt/toolchains/arm-eabi-4.7/bin/arm-eabi-
export CROSS_COMPILE=/opt/toolchains/arm-cortex_a15-linux-gnueabihf-linaro_4.9/bin/arm-cortex_a15-linux-gnueabihf-
mkdir output

BUILD_JOB_NUMBER=`grep processor /proc/cpuinfo|wc -l`

make -C $(pwd) O=output VARIANT_DEFCONFIG=msm8974_sec_hlte_eur_defconfig \
			ahmed_msm8974_sec_defconfig SELINUX_DEFCONFIG=selinux_defconfig || exit -1
make -C $(pwd) O=output -j$BUILD_JOB_NUMBER || exit -1

tools/dtbTool -p output/scripts/dtc/ -s 2048 -o output/arch/arm/boot/ffffff.dtb output/arch/arm/boot/
tools/mkbootimg --tags_offset 0x01e00000 --ramdisk_offset 0x02000000 --kernel output/arch/arm/boot/zImage \
			--ramdisk boot_image/boot.img-ramdisk.gz \
			--cmdline 'console=null androidboot.hardware=qcom user_debug=23 msm_rtb.filter=0x37 ehci-hcd.park=3' \
			--base 0x00000000 --pagesize 2048 --dt output/arch/arm/boot/ffffff.dtb -o boot_image/boot.img
cd boot_image/
DATE_STR=`date +"%H_%M_%S__%d-%m-%Y"`
cp zip_recovery.zip $DATE_STR.zip
zip -u $DATE_STR.zip boot.img
cd -
tar cf boot_image/$DATE_STR.tar -C boot_image/ boot.img && rm boot_image/boot.img
#cp output/arch/arm/boot/Image $(pwd)/arch/arm/boot/zImage
