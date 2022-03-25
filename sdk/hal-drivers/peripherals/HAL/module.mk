# Module High Abstraction Level -----------------

MODULE_DIR_HAL := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

INCLUDES += -I$(MODULE_DIR_HAL)inc

$(TARGET_SDK) : CFILES +=   $(MODULE_DIR_HAL)src/hal_gpio.c \
							$(MODULE_DIR_HAL)src/hal_usart.c \
							$(MODULE_DIR_HAL)src/hal_i2c.c
