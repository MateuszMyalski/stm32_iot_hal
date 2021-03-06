#include <stdbool.h>

#include "bsp.h"
#include "hal_gpio.h"
#include "utils.h"

int bsp_init_led(void) {
    int err = 0;

    err = hal_gpio_open(BSP_GREEN_LED_PORT);
    ExitOnError(err);
    err = hal_gpio_open(BSP_RED_LED_PORT);
    ExitOnError(err);
    err = hal_gpio_open(BSP_USER_BUTTON_PORT);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, gpio_ioctl_output);
    ExitOnError(err);
    err = hal_gpio_ioctl(BSP_RED_LED_PORT, BSP_RED_LED_PIN, gpio_ioctl_output);
    ExitOnError(err);
    err = hal_gpio_ioctl(BSP_USER_BUTTON_PORT, BSP_USER_BUTTON_PIN, gpio_ioctl_digital_input);
    ExitOnError(err);

    err = hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, true);
    ExitOnError(err);
    err = hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, true);
    ExitOnError(err);

exit:
    return err;
}