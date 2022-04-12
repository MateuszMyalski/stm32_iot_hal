#include "bsp.h"
#include "ll_clock.h"
#include "utils.h"

#ifdef USE_SEMIHOSTING
extern void initialise_monitor_handles(void);
#endif  // USE_SEMIHOSTING

extern uint32_t SystemCoreClock;

int bsp_init_clock(void) {
    ll_clock_system_switch_HSI16(RCC);
    ll_clock_hsi_on(RCC);

    SystemCoreClockUpdate();

    return 0;
}

int bsp_init(void) {
    int err = 0;

#ifdef USE_SEMIHOSTING
    initialise_monitor_handles();
#endif  // USE_SEMIHOSTING

    err = bsp_init_clock();
    Assert(0 == err);

    err = SysTick_Config(SystemCoreClock / 1000);
    Assert(0 == err);

    err = bsp_init_led();
    Assert(0 == err);

    err = bsp_init_periphs();
    Assert(0 == err);

    return err;
}