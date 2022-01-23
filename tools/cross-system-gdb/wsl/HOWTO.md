# How to run cross system debug
1. Prerequsites
   1. ST-LINK GDB server (can be from CubeIDE or standalone) - https://www.st.com/en/development-tools/st-link-server.html
   2. STM32CubeProg - https://www.st.com/en/development-tools/stm32cubeprog.html
2. Run WSL
3. Edit `gdb-server-run.sh` by providing path to the tools
4. Check windows local IP
5. Start GDB in the new tab `./tools/toolchain/linux/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gdb out/<file>.elf`
6. Connect to the remote server in GDB by `target remote <windows_machine_local_ip>:3333`