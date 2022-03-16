#include "bsp.h"
#include "delay.h"
#include "ee_storage.h"
#include "hal_gpio.h"

bool factory_reset_check_trigger(void) {
    bool user_button = hal_gpio_read(BSP_USER_BUTTON_PORT, BSP_USER_BUTTON_PIN);
    if (user_button) {
        delay_ms(50);  // Simple debouncing for current state of art
        if (user_button) {
            return true;
        }
    }

    return false;
}

void factory_reset_handle(void) {
    ee_storage_factory_reset();
}
