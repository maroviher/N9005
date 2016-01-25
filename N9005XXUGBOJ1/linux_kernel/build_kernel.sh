#!/bin/bash

export ARCH=arm
export CROSS_COMPILE=/opt/toolchains/arm-eabi-4.7/bin/arm-eabi-
mkdir output

make -C $(pwd) O=output VARIANT_DEFCONFIG=msm8974_sec_hlte_eur_defconfig msm8974_sec_defconfig SELINUX_DEFCONFIG=selinux_defconfig
make -C $(pwd) O=output -j5

tools/dtbTool -p output/scripts/dtc/ -s 2048 -o output/arch/arm/boot/ffffff.dtb output/arch/arm/boot/
tools/mkbootimg --kernel output/arch/arm/boot/zImage --ramdisk boot_image/boot.img-ramdisk.gz --cmdline 'console=null androidboot.hardware=qcom user_debug=23 msm_rtb.filter=0x37 ehci-hcd.park=3' --base 0x00000000 --pagesize 2048 --dt output/arch/arm/boot/ffffff.dtb -o boot_image/boot.img
cd boot_image
tar cf "`date +"%H_%m_%S__%_d-%m-%Y"`.tar" boot.img && rm boot.img
cd -
#cp output/arch/arm/boot/Image $(pwd)/arch/arm/boot/zImage