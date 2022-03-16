# Module Peripherials ---------------------------

MODULE_DIR_PERIPHERALS := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

include $(MODULE_DIR_PERIPHERALS)CMSIS/module.mk
include $(MODULE_DIR_PERIPHERALS)HAL/module.mk
include $(MODULE_DIR_PERIPHERALS)LL/module.mk
