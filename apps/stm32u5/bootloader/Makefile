# -*- MakeFile -*-

# TODO(Mateusz) Move this to seperate config file
# TODO(Mateusz) Do not use abs paths
TOOLCHAIN_PATH := /mnt/c/Users/Mateu/Desktop/Repositories/stm_hal/tools/toolchain/linux/gcc-arm-none-eabi-10.3-2021.10/bin
ARM_NONE_EABI_BASE := $(TOOLCHAIN_PATH)/arm-none-eabi-

AS   := $(ARM_NONE_EABI_BASE)as
CC   := $(ARM_NONE_EABI_BASE)gcc
CCX  := $(ARM_NONE_EABI_BASE)g++
AR   := $(ARM_NONE_EABI_BASE)ar
LD   := $(ARM_NONE_EABI_BASE)ld
OC   := $(ARM_NONE_EABI_BASE)objcopy
OD   := $(ARM_NONE_EABI_BASE)objdump
OS   := $(ARM_NONE_EABI_BASE)size

LDSCRIPTS_PATH := /mnt/c/Users/Mateu/Desktop/Repositories/stm_hal/link
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

%.o: %.c
	@echo "[Compiling:" $< "]"
	$(CC) $(CFLAGS) $< -o $@

%.o: %.S
	@echo "[Compiling:" $< "]"
	$(CC) -x assembler-with-cpp $(SFLAGS) $< -o $@

# -----------------------------------

TARGET := stm32u5_bootloader
MARCH      := cortex-m33

CFLAGS   := -c \
			-mcpu=$(MARCH) \
			-mthumb \
			-O0 \
			-Wall \
			-Wl,--gc-sections

LDSCRIPT := stm32u5.ld
LFLAGS   := -mcpu=$(MARCH) \
			-mthumb \
			-Os \
			--specs=nosys.specs \
			-nostdlib \
			-lgcc \
			-T$(LDSCRIPTS_PATH)/$(LDSCRIPT)

CFILES   := main.c




OBJS := $(patsubst %.c, %.o, $(CFILES))
OBJS += $(AS_SRC:.S=.o)

.PHONY: all
all : $(TARGET).elf

.PHONY: info
info:
	@echo
	@echo "---[VARIABLES]---"
	@echo "[TOOLCHAIN]:" $(ARM_NONE_EABI_BASE)
	@echo "[ARM_NONE_EABI_BASE]:" $(ARM_NONE_EABI_BASE)
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
	rm -f $(OBJS)
	rm -f $(TARGET).elf

$(TARGET).elf: $(OBJS)
	@echo "[Linking:" $@ "]"
	$(CC) $^ $(LFLAGS) -o $@



