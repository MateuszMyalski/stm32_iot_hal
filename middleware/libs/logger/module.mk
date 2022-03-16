# Library LOGGER --------------------------------

MODULE_DIR_LIB_LOGGER := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
LIB_LOGGER_OUT_PATH   := $(OUT_PATH)/lib/logger
LIB_LOGGER            := $(LIB_LOGGER_OUT_PATH)/lib/liblogger.a

# LIBS      += $(LIB_LOGGER)
INCLUDES  += -I$(MODULE_DIR_LIB_LOGGER)inc

include $(MIDDLEWARE_PATH)/libs/tiny_printf/module.mk

$(LIB_LOGGER) : CFILES := $(NULL)
$(LIB_LOGGER) : OBJS   := $(patsubst $(MODULE_DIR_LIB_LOGGER)src/%.c, $(LIB_LOGGER_OUT_PATH)/%.o, $(CFILES))

.SECONDEXPANSION:
$(LIB_LOGGER): $$(OBJS)
	$(QUIET)$(ECHO) "[Archiving:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(LIB_LOGGER_OUT_PATH)
	$(QUIET)$(AR) rcu $@ $^

$(LIB_LOGGER_OUT_PATH)/%.o: $(MODULE_DIR_LIB_LOGGER)/src/%.c
	$(QUIET)$(ECHO) "[Compiling:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(dir $@)
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) $< -o $@
