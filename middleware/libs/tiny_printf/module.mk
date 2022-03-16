# Library Tiny Printf ---------------------------

MODULE_DIR_LIB_TINYPRINTF := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
LIB_TINYPRINTF_OUT_PATH   := $(OUT_PATH)/lib/tiny_printf
LIB_TINYPRINTF            := $(LIB_TINYPRINTF_OUT_PATH)/libtinyprintf.a

LIBS     += $(LIB_TINYPRINTF)
INCLUDES += -I$(MODULE_DIR_LIB_TINYPRINTF)inc

$(LIB_TINYPRINTF) : CFILES := $(MODULE_DIR_LIB_TINYPRINTF)src/tiny_printf.c
$(LIB_TINYPRINTF) : OBJS   := $(patsubst $(MODULE_DIR_LIB_TINYPRINTF)src/%.c, $(LIB_TINYPRINTF_OUT_PATH)/%.o, $(CFILES))

.SECONDEXPANSION:
$(LIB_TINYPRINTF): $$(OBJS)
	$(QUIET)$(ECHO) "[Archiving:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(LIB_TINYPRINTF_OUT_PATH)
	$(QUIET)$(AR) rcu $@ $^

$(LIB_TINYPRINTF_OUT_PATH)/%.o: $(MODULE_DIR_LIB_TINYPRINTF)src/%.c
	$(QUIET)$(ECHO) "[Compiling:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(dir $@)
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) $< -o $@
