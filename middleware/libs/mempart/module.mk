# Library Mempart -------------------------------

MODULE_DIR_LIB_MEMPART := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
LIB_MEMPART_OUT_PATH   := $(OUT_PATH)/lib/mempart
LIB_MEMPART            := $(LIB_MEMPART_OUT_PATH)/libmempart.a

LIBS     += $(LIB_MEMPART)
INCLUDES += -I$(MODULE_DIR_LIB_MEMPART)inc

include $(MIDDLEWARE_PATH)/libs/crc/module.mk

$(LIB_MEMPART) : CFILES :=  $(MODULE_DIR_LIB_MEMPART)src/mempart.c \
							$(MODULE_DIR_LIB_MEMPART)src/partmng.c
$(LIB_MEMPART) : OBJS   := $(patsubst $(MODULE_DIR_LIB_MEMPART)src/%.c, $(LIB_MEMPART_OUT_PATH)/%.o, $(CFILES))

.SECONDEXPANSION:
$(LIB_MEMPART): $$(OBJS)
	$(QUIET)$(ECHO) "[Archiving:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(LIB_MEMPART_OUT_PATH)
	$(QUIET)$(AR) rcu $@ $^

$(LIB_MEMPART_OUT_PATH)/%.o: $(MODULE_DIR_LIB_MEMPART)/src/%.c
	$(QUIET)$(ECHO) "[Compiling:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(dir $@)
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) $< -o $@
