# -*- MakeFile -*-

LIBLOGGER_CFILES := logger/tiny_printf.c
INCLUDES         += -I$(PROJECT_PATH)/logger/include

LIBLOGGER_OBJS := $(patsubst %.c, $(OUT_OBJ_PATH)/%.o, $(LIBLOGGER_CFILES))

$(OUT_LIB_PATH)/liblogger.a: $(LIBLOGGER_OBJS)
	@echo "[Archiving:" $(notdir $@)"]"
	@mkdir -p $(dir $@)
	@$(AR) rcu $@ $^
