#!/bin/bash
export ARCH=arm
export CROSS_COMPILE=/home/haiviet/gcc/bin/arm-eabi-
make ef47s_user_defconfig
make -j2
