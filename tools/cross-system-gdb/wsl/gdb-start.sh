#!/bin/bash
GDB_PATH='tools/toolchain/linux/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gdb'
GDB_FALGS="-ex 'target remote $1:3333'"
GDB_START="${GDB_PATH} $2 ${GDB_FALGS}"

echo
echo "Seems that arm-none-eabii-gdb has bug so -ex flag is not forwarded just copy generated line"
echo
echo ${GDB_START}
echo