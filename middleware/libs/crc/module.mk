# Library CRC -----------------------------------

MODULE_DIR_LIB_CRC := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
LIB_CRC_OUT_PATH   := $(OUT_PATH)/lib/crc
LIB_CRC            := $(LIB_CRC_OUT_PATH)/libcrc.a

LIBS      += $(LIB_CRC)
INCLUDES  += -I$(MODULE_DIR_LIB_CRC)inc

$(LIB_CRC) : CFILES := $(MODULE_DIR_LIB_CRC)src/crc32.c
$(LIB_CRC) : OBJS   := $(patsubst $(MODULE_DIR_LIB_CRC)src/%.c, $(LIB_CRC_OUT_PATH)/%.o, $(CFILES))

.SECONDEXPANSION:
$(LIB_CRC): $$(OBJS)
	$(QUIET)$(ECHO) "[Archiving:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(LIB_CRC_OUT_PATH)
	$(QUIET)$(AR) rcu $@ $^

$(LIB_CRC_OUT_PATH)/%.o: $(MODULE_DIR_LIB_CRC)src/%.c
	$(QUIET)$(ECHO) "[Compiling:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(dir $@)
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) $< -o $@
