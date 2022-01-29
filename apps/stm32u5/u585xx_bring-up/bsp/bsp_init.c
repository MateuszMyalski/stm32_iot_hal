#include "bsp.h"
#include "logger.h"
#include "stm32u585xx.h"

#ifdef USE_SEMIHOSTING
extern void initialise_monitor_handles(void);
#endif  // USE_SEMIHOSTING

int bsp_init(void) {
    int err = 0;
    err = SysTick_Config(SystemCoreClock / 1000);
    if (0 != err) {
        LOG_ERR("Cannot initialize SysTick_Config\n");
        ExitOnError(err);
    }
    LOG_INFO("Initialized Systick\n");

    err = bsp_init_led();
    if (0 != err) {
        LOG_ERR("Cannot initialize bsp_init_led\n");
        ExitOnError(err);
    }
    LOG_INFO("Initialized bsp_init_led\n");

#ifdef USE_SEMIHOSTING
    LOG_WARNING("USE_SEMIHOSTING defined\n");
    initialise_monitor_handles();
    LOG_INFO("Initialized initialise_monitor_handles\n");
#endif  // USE_SEMIHOSTING

exit:
    return err;
}