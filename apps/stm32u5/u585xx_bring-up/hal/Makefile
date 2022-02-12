# -*- MakeFile -*-

LIBHAL_CFILES := hal/hal_gpio.c \
				hal/hal_i2c.c

SDK_CFILES := hal/sdk/sdk_gpio.c \
            hal/sdk/sdk_i2c.c

INCLUDES += -I$(PROJECT_PATH)/hal/include \
			-I$(PROJECT_PATH)/hal/sdk/include

LIBHAL_OBJS := $(patsubst %.c, $(OUT_OBJ_PATH)/%.o, $(LIBHAL_CFILES))
SDK_OBJS := $(patsubst %.c, $(OUT_OBJ_PATH)/%.o, $(SDK_CFILES))

$(OUT_LIB_PATH)/libhal.a: $(LIBHAL_OBJS) $(SDK_OBJS)
	@echo "[Archiving:" $(notdir $@)"]"
	@mkdir -p $(dir $@)
	@$(AR) rcu $@ $^
