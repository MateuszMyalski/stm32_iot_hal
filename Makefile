# -*- MakeFile -*-

# TOOLCHAIN CONFIGURATION
TOOLCHAIN_PATH := $(CURDIR)/tools/toolchain/linux/gcc-arm-none-eabi-10.3-2021.10/bin
ARM_NONE_EABI_PREFIX := $(TOOLCHAIN_PATH)/arm-none-eabi

AS   := $(ARM_NONE_EABI_PREFIX)-as
CC   := $(ARM_NONE_EABI_PREFIX)-gcc
CCX  := $(ARM_NONE_EABI_PREFIX)-g++
AR   := $(ARM_NONE_EABI_PREFIX)-ar
LD   := $(ARM_NONE_EABI_PREFIX)-ld
OC   := $(ARM_NONE_EABI_PREFIX)-objcopy
OD   := $(ARM_NONE_EABI_PREFIX)-objdump
OS   := $(ARM_NONE_EABI_PREFIX)-size

# DIRECTORIES
OUT_PATH := $(CURDIR)/out
OBJ_PATH := $(OUT_PATH)/obj

APPS_PATH := $(CURDIR)/apps
LINK_PATH := $(CURDIR)/link

# INIT TARGET FLAGS
LDSCRIPT := $(NULL)
CPPFLAGS := $(NULL)
CFLAGS   := $(NULL)
LFLAGS   := $(NULL)
INCLUDES := $(NULL)
CFILES   := $(NULL)
SFLAGS   := $(NULL)
SFILES   := $(NULL)
OBJS     := $(NULL)
LIBS     := $(NULL)

# HELPER RECIPS
.PHONY: info
info:
	@echo
	@echo "---[VARIABLES]---"
	@echo "[TOOLCHAIN]:" $(ARM_NONE_EABI_PREFIX)
	@echo "[TARGET NAME]:" $(TARGET)
	@echo "[L FLAGS]:" $(LFLAGS)
	@echo "[S FLAGS]:" $(SFLAGS)
	@echo "[C FLAGS]:" $(CFLAGS)
	@echo "[CPP FLAGS]:" $(CPPFLAGS)
	@echo "[INCLUDES]:" $(INCLUDES)
	@echo "[LINKER SCRIPT]:" $(LDSCRIPT)
	@echo "[S FILES]:" $(SFILES)
	@echo "[C FILES]:" $(CFILES)
	@echo "[LIBS]:" $(LIBS)
	@echo "-----------------"
	@echo

.PHONY: clean
clean:
	@echo "[Cleaning up the project]"
	rm -rf $(OUT_PATH)

# SELECT TARGET
# TODO(Mateusz) Currently hardcoded stm32u5 target
include $(APPS_PATH)/stm32u5/basic/Makefile.target