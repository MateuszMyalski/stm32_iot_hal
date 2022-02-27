#include "bsp.h"
#include "delay.h"
#include "hal_gpio.h"
#include "memory.h"
#include "modules.h"

bool check_factory_reset_trigger(void) {
    bool user_button = hal_gpio_read(BSP_USER_BUTTON_PORT, BSP_USER_BUTTON_PIN);
    if (user_button) {
        delay_ms(50);  // Simple debouncing for current state of art
        if (user_button) {
            return true;
        }
    }

    return false;
}

void handle_factory_reset(void) {
    factory_reset_eeprom();
}
