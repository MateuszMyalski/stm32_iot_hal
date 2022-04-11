# Application MFG -------------------------------

TARGET             := appMFG
MARCH              := cortex-m33
APP_PATH           := $(APPS_PATH)/$(TARGET)
APP_SRC_PATH       := $(APP_PATH)/src
APP_OUT_PATH       := $(OUT_PATH)/$(TARGET)
APP_LINK_PATH      := $(APP_PATH)/link
LDSCRIPT           := $(APP_LINK_PATH)/stm32u5xx_linker.ld
OPTIMISATION_FLAGS := -O0 -g

INCLUDES += -I$(APP_PATH)/inc

CFLAGS   := -c \
			-mcpu=$(MARCH) \
			-mthumb \
			$(OPTIMISATION_FLAGS) \
			-Wall \
			-Wl,--gc-sections

SFLAGS   := $(CFLAGS)

LFLAGS   := -mcpu=$(MARCH) \
			-mthumb \
			$(OPTIMISATION_FLAGS) \
			--specs=nano.specs \
			-lgcc \
			-Wl,--print-memory-usage \
			-T$(LDSCRIPT)

$(TARGET).elf: CFILES_TESTS := $(APP_SRC_PATH)/tests/hts221_test.c

$(TARGET).elf: CFILES   :=  $(APP_SRC_PATH)/main.c \
							$(APP_SRC_PATH)/delay.c \
							$(APP_SRC_PATH)/factory_reset.c \
							$(APP_SRC_PATH)/led_notifier.c \
							$(APP_SRC_PATH)/syscalls.c \
							$(APP_SRC_PATH)/system_stm32u5xx.c \
							$(APP_SRC_PATH)/handlers.c \
							$(APP_SRC_PATH)/ee_storage.c \
							$(CFILES_TESTS)

$(TARGET).elf : SFILES  :=  $(APP_SRC_PATH)/startup_stm32u585xx.s

$(TARGET).elf : OBJS := $(patsubst $(APP_SRC_PATH)/%.c, $(APP_OUT_PATH)/%.o, $(CFILES))
$(TARGET).elf : OBJS += $(patsubst $(APP_SRC_PATH)/%.s, $(APP_OUT_PATH)/%.o, $(SFILES))

# Include modules -------------------------------
LIBS := $(NULL)

include $(APP_PATH)/module.cfg
include $(SDK_PATH)/module.mk
include $(MIDDLEWARE_PATH)/libs/mempart/module.mk
include $(MIDDLEWARE_PATH)/libs/logger/module.mk
include $(MIDDLEWARE_PATH)/libs/crc/module.mk

.SECONDEXPANSION:
$(TARGET).elf: $$(OBJS) $(LIBS)
	$(QUIET)$(ECHO) "[Linking:" $(notdir $@)"]"
	$(QUIET)$(CC) $^ $(LFLAGS) $(LIBS) -o $(OUT_PATH)/$@

$(TARGET).hex: $(TARGET).elf
	@echo "[Generating hex:" $(notdir $@)"]"
	$(QUIET)$(OC) -O ihex $(APP_OUT_PATH).elf $(APP_OUT_PATH).hex
	$(QUIET)$(OD) -D $(APP_OUT_PATH).elf > $(OUT_PATH)/obj-dump-$(TARGET).lst
	$(QUIET)$(OD) -t $(APP_OUT_PATH).elf > $(OUT_PATH)/obj-dump-$(TARGET).map
	$(QUIET)$(OD) -h $(APP_OUT_PATH).elf > $(OUT_PATH)/obj-dump-sections-$(TARGET).map

$(APP_OUT_PATH)/%.o: $(APP_SRC_PATH)/%.c
	$(QUIET)$(ECHO) "[Compiling:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(dir $@)
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

$(APP_OUT_PATH)/%.o: $(APP_SRC_PATH)/%.s
	$(QUIET)$(ECHO) "[Syntezing:" $(notdir $@)"]"
	$(QUIET)$(MKDIR) $(dir $@)
	$(QUIET)$(CC) -x assembler-with-cpp $(INCLUDES) $(SFLAGS) $< -o $@
