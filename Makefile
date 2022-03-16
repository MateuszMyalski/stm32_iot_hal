# -*- MakeFile -*-

# Toolchain configuration -----------------------
ENV_CFG_PATH := $(CURDIR)/env.cfg

ifneq ($(shell test -e $(ENV_CFG_PATH) && echo -n yes),yes)
	$(error "Project not configured! Run ./tools/envsetup.sh")
endif

include $(ENV_CFG_PATH)

ARM_NONE_EABI_PREFIX := $(TOOLCHAIN_BIN_PATH)/arm-none-eabi

AS    := $(ARM_NONE_EABI_PREFIX)-as
CC    := $(ARM_NONE_EABI_PREFIX)-gcc
CXX   := $(ARM_NONE_EABI_PREFIX)-g++
AR    := $(ARM_NONE_EABI_PREFIX)-ar
LD    := $(ARM_NONE_EABI_PREFIX)-ld
OC    := $(ARM_NONE_EABI_PREFIX)-objcopy
OD    := $(ARM_NONE_EABI_PREFIX)-objdump
OS    := $(ARM_NONE_EABI_PREFIX)-size

QUIET := @
ECHO  := echo
MKDIR := mkdir -p

# Main directories ------------------------------
OUT_PATH        := $(CURDIR)/out
APPS_PATH       := $(CURDIR)/app
MIDDLEWARE_PATH := $(CURDIR)/middleware
SDK_PATH        := $(CURDIR)/sdk

# Select target ---------------------------------
include $(APPS_PATH)/$(APP_NAME)/module.mk

.PHONY: info
info:
	$(QUIET)$(ECHO)
	$(QUIET)$(ECHO) "---[Build set]---"
	$(QUIET)$(ECHO) "[TOOLCHAIN]:" $(TOOLCHAIN_BIN_PATH)
	$(QUIET)$(ECHO) "[TARGET NAME]:" $(TARGET)
	$(QUIET)$(ECHO) "[APP NAME]:" $(APP_NAME)
	$(QUIET)$(ECHO) "-----------------"
	$(QUIET)$(ECHO)

.PHONY: clean
clean:
	$(QUIET)$(ECHO) "[Cleaning up the project]"
	rm -rf $(OUT_PATH)

.PHONY: all
all: $(TARGET).hex
