# -*- MakeFile -*-

LIBEXTMEM_CFILES := extmem/partition.c \
                    extmem/eeprom.c \
                    extmem/crc32.c

INCLUDES         += -I$(PROJECT_PATH)/extmem/include

LIBEXTMEM_OBJS := $(patsubst %.c, $(OUT_OBJ_PATH)/%.o, $(LIBEXTMEM_CFILES))

$(OUT_LIB_PATH)/libextmem.a: $(LIBEXTMEM_OBJS)
	@echo "[Archiving:" $(notdir $@)"]"
	@mkdir -p $(dir $@)
	@$(AR) rcu $@ $^
