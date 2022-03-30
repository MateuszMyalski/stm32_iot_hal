# Module Low Level ------------------------------

MODULE_DIR_LL := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

INCLUDES  += -I$(MODULE_DIR_LL)inc

$(TARGET_SDK) : CFILES += $(MODULE_DIR_LL)src/ll_gpio.c \
						  $(MODULE_DIR_LL)src/ll_i2c.c \
						  $(MODULE_DIR_LL)src/ll_clock.c \
						  $(MODULE_DIR_LL)src/ll_crc.c
