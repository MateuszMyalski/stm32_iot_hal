# Module EEPROM ---------------------------------

MODULE_DIR_EEPROM := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

INCLUDES += -I$(MODULE_DIR_EEPROM)inc

$(TARGET_SDK) : CFILES += $(MODULE_DIR_EEPROM)src/eeprom.c
