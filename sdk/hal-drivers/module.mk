# Module Hal Drivers ----------------------------

MODULE_DIR_DRIVERS := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

include $(MODULE_DIR_DRIVERS)devices/module.mk
include $(MODULE_DIR_DRIVERS)peripherals/module.mk
