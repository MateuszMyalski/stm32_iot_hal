# Module Devices --------------------------------

MODULE_DIR_DEVICES := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

include $(MODULE_DIR_DEVICES)hts221/module.mk
include $(MODULE_DIR_DEVICES)eeprom/module.mk
