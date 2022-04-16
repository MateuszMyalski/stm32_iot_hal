# Module CMSIS ----------------------------------

MODULE_DIR_CMSIS := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

INCLUDES += -I$(MODULE_DIR_CMSIS)inc
