# Module SDK ------------------------------------

MODULE_DIR_SDK := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SDK_OUT_PATH   := $(OUT_PATH)/sdk
TARGET_SDK     := $(SDK_OUT_PATH)/libsdk.a
LIBS           += $(TARGET_SDK)

include $(MODULE_DIR_SDK)hal-drivers/module.mk
include $(MODULE_DIR_SDK)bsp/module.mk

$(TARGET_SDK) : OBJS := $(patsubst $(SDK_PATH)/%.c, $(SDK_OUT_PATH)/%.o, $(CFILES))

.SECONDEXPANSION:
$(TARGET_SDK): $$(OBJS)
	$(QUIET)$(ECHO) "[Archiving:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(SDK_OUT_PATH)
	$(QUIET)$(AR) rcu $@ $^

$(SDK_OUT_PATH)/%.o: $(SDK_PATH)/%.c
	$(QUIET)$(ECHO) "[Compiling:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(dir $@)
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) $< -o $@
