#!/bin/bash
export ARCH=arm
export CROSS_COMPILE=/home/haiviet/gcc/bin/arm-eabi-

mkdir -p ./obj/KERNEL_OBJ/
make ARCH=arm O=./obj/KERNEL_OBJ/ msm8960_ef45k_tp20_user_defconfig
make -j2 ARCH=arm O=./obj/KERNEL_OBJ/
cp -f ./obj/KERNEL_OBJ/arch/arm/boot/zImage .
