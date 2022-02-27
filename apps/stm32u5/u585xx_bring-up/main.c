#include <stdlib.h>
#include <string.h>

#include "bsp.h"
#include "logger.h"
#include "modules.h"

int main() {
    bsp_init();

    if(check_factory_reset_trigger()) {
        LOG_WARN("Factory reset triggered!\r\n");
        handle_factory_reset();
    }

    hts221_simple_test();

    part_device_info_t device_info = {};
    get_device_info(&device_info);


    while (1) {
        idle_notifier();
    }
}
