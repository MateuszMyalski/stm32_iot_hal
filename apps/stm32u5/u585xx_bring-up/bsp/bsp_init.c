#include "bsp.h"
#include "logger.h"
#include "stm32u585xx.h"
#include "stm32u5xx.h"

#ifdef USE_SEMIH
OSTING
extern void initialise_monitor_handles(void);
#endif  // USE_SEMIHOSTING

extern uint32_t SystemCoreClock;

int bsp_init_clock() {
    /* Reconfigure the clock to use HSI 16MHz clock */
    MODIFY_REG(RCC->CFGR1, RCC_CFGR1_SW, 0x01UL << RCC_CFGR1_SW_Pos);
    SET_BIT(RCC->CR, RCC_CR_HSION);

    SystemCoreClockUpdate();
    return 0;
}

int bsp_init(void) {
    int err = 0;

#ifdef USE_SEMIHOSTING
    LOG_WARNING("USE_SEMIHOSTING defined\n");
    initialise_monitor_handles();
    LOG_INFO("Initialized initialise_monitor_handles\n");
#endif  // USE_SEMIHOSTING

    err = bsp_init_clock();
    if (0 != err) {
        LOG_ERR("Cannot initialize bsp_init_clock\n");
        ExitOnError(err);
    }

    LOG_INFO("Device clock reconfigured to: %d Hz\n", SystemCoreClock);

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

    err = bsp_init_periphs();
    if (0 != err) {
        LOG_ERR("Cannot initialize bsp_init_periphs\n");
        ExitOnError(err);
    }
    LOG_INFO("Initialized bsp_init_periphs\n");

exit:
    while (0 != err) {
        // Hang in init on error
    }
    return err;
}