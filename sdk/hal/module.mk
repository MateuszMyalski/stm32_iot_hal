# Module Hal Drivers ----------------------------

MODULE_DIR_DRIVERS := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

include $(MODULE_DIR_DRIVERS)cmsis/module.mk
include $(MODULE_DIR_DRIVERS)high-level/module.mk
include $(MODULE_DIR_DRIVERS)low-level/module.mk
