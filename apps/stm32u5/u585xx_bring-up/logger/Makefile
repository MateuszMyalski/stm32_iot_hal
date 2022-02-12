# -*- MakeFile -*-

LIBLOG_CFILES     := logger/tiny_printf.c
INCLUDES          += -I$(PROJECT_PATH)/logger/include

LIBLOG_OBJS := $(patsubst %.c, $(OUT_OBJ_PATH)/%.o, $(LIBLOG_CFILES))

$(OUT_LIB_PATH)/liblog.a: $(LIBLOG_OBJS)
	@echo "[Archiving:" $(notdir $@)"]"
	@mkdir -p $(dir $@)
	@$(AR) rcu $@ $^
