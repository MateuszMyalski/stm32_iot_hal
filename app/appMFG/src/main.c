#include "bsp.h"
#include "ee_storage.h"
#include "eeprom_map.h"
#include "factory_reset.h"
#include "hts221_test.h"
#include "led_notifier.h"
#include "logger.h"

int main() {
    bsp_init();
    init_ee_storage();

    LOG_INFO("Build: " BUILD_USER "\r\n");

    if (factory_reset_check_trigger()) {
        LOG_WARN("Factory reset triggered!\r\n");
        factory_reset_handle();
        led_notifier_happy_blink();
    }

    hts221_test();

    part_device_info_t device_info = {};
    ee_storage_get_device_info(&device_info);

    while (1) {
        LOG_INFO("Idle state...\r\n");
        led_notifier_idle();
    }
}
