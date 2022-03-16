# Module HTS221 ---------------------------------

MODULE_DIR_HTS221 := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

INCLUDES += -I$(MODULE_DIR_HTS221)inc

$(TARGET_SDK) : CFILES += $(MODULE_DIR_HTS221)src/hts221.c
