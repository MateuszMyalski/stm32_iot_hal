# Module BSP ------------------------------------

MODULE_DIR_BSP := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

INCLUDES   += -I$(MODULE_DIR_BSP)inc

$(TARGET_SDK) : CFILES +=   $(MODULE_DIR_BSP)src/bsp_init.c \
							$(MODULE_DIR_BSP)src/bsp_utils.c \
							$(MODULE_DIR_BSP)src/led.c \
							$(MODULE_DIR_BSP)src/periphs.c
