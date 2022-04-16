# Module Devices --------------------------------

MODULE_DIR_DEVICES := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SENSOR_DIR = $(MODULE_DIR_DEVICES)/sensor
MEMORY_DIR = $(MODULE_DIR_DEVICES)/memory

# Sensors
include $(SENSOR_DIR)/hts221/module.mk

# Memories
include $(MEMORY_DIR)/eeprom/module.mk
