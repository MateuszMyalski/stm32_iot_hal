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
CORE_PATH := $(CURDIR)/core

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
include $(APPS_PATH)/stm32u5/u585xx_base/Makefile.target

.PHONY: all
all : $(TARGET).hex

$(TARGET).elf: $(OBJS)
	@echo "[Linking:" $@"]"
	@$(CC) $^ $(LFLAGS) -o $(OUT_PATH)/$@

$(TARGET).hex: $(TARGET).elf
	@echo "[Generating hex:" $@"]"
	@$(OC) -O ihex $(OUT_PATH)/$(TARGET).elf $(OUT_PATH)/$(TARGET).hex
	@$(OD) -D $(OUT_PATH)/$(TARGET).elf > $(OUT_PATH)/obj-dump-$(TARGET).lst
	@$(OD) -t $(OUT_PATH)/$(TARGET).elf > $(OUT_PATH)/obj-dump-$(TARGET).map
	@$(OD) -h $(OUT_PATH)/$(TARGET).elf > $(OUT_PATH)/obj-dump-sections-$(TARGET).map

$(OBJ_PATH)/%.o: $(PROJECT_PATH)/%.c
	@echo "[Compiling:" $@"]"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

$(OBJ_PATH)/%.o: $(PROJECT_PATH)/%.s
	@echo "[Syntezing:" $@"]"
	@mkdir -p $(dir $@)
	@$(CC) -x assembler-with-cpp $(INCLUDES) $(SFLAGS) $< -o $@