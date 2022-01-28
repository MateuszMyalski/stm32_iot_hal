#!/bin/bash

# Specify path to the ST-LINK server
# in e.g. /mnt/d/STM32CubeIDE_1.6.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.win32_1.6.0.202101291314/tools/bin
# WIN_PATH e.g. D:\STM32CubeProgrammer\bin
ST_LINK_SERVER_PATH_WIN_PATH='D:\STM32CubeProgrammer\bin'
ST_LINK_SERVER_PATH='/mnt/d/STM32CubeIDE_1.6.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.win32_1.6.0.202101291314/tools/bin'

# Specify path to the CUBE Programmer
# in e.g. /mnt/d/STM32CubeProgrammer/bin
CUBE_PROGRAMMER_PATH='/mnt/d/STM32CubeProgrammer/bin'

GDB_SERVER="${ST_LINK_SERVER_PATH}/ST-LINK_gdbserver.exe"

# Based on original config.txt from ST-LINK server
SERVER_FLAGS="-e -f debug.log -p 3333 -r 15 -d -t -cp ${ST_LINK_SERVER_PATH_WIN_PATH}"

${GDB_SERVER} ${SERVER_FLAGS} &
