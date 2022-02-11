#include "hal_gpio.h"
#include <stdbool.h>
#include "hal_common.h"
#include "sdk_gpio.h"

#define MAX_PIN_NUM_IN_PORT 16U

static bool sanity_check(GPIO_TypeDef *GPIO_port, uint32_t GPIO_pin) {
    if (!IS_GPIO_ALL_INSTANCE(GPIO_port)) {
        return -1;
    }

    if (GPIO_pin >= MAX_PIN_NUM_IN_PORT) {
        return -1;
    }

    return 0;
}

int hal_gpio_open(GPIO_TypeDef *GPIO_port) {
    if (sanity_check(GPIO_port, 0) != 0) {
        return -1;
    }

    sdk_gpio_enable_AHB(GPIO_port);

    return 0;
}

int hal_gpio_close(GPIO_TypeDef *GPIO_port) {
    if (sanity_check(GPIO_port, 0) != 0) {
        return -1;
    }

    sdk_gpio_disable_AHB(GPIO_port);

    return 0;
}

int hal_gpio_ioctl(GPIO_TypeDef *GPIO_port, uint32_t GPIO_pin, gpio_ioctl_t gpio_ioctl) {
    if (sanity_check(GPIO_port, GPIO_pin) != 0) {
        return -1;
    }

    switch (gpio_ioctl) {
        case gpio_ioctl_digital_input:
            sdk_gpio_mode_digital_in(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_output:
            sdk_gpio_mode_out(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_analog_input:
            sdk_gpio_mode_analog_in(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_alternate:
            sdk_gpio_mode_alt(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_push_pull:
            sdk_gpio_type_pp(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_open_drain:
            sdk_gpio_type_od(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_low_speed:
            sdk_gpio_speed_low(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_medium_speed:
            sdk_gpio_speed_medium(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_high_speed:
            sdk_gpio_speed_high(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_very_high_speed:
            sdk_gpio_speed_very_high(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_no_pull:
            sdk_gpio_no_pull(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_pull_up:
            sdk_gpio_pull_up(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_pull_down:
            sdk_gpio_pull_down(GPIO_port, GPIO_pin);
            break;
        case gpio_ioctl_af_0:
        case gpio_ioctl_af_1:
        case gpio_ioctl_af_2:
        case gpio_ioctl_af_3:
        case gpio_ioctl_af_4:
        case gpio_ioctl_af_5:
        case gpio_ioctl_af_6:
        case gpio_ioctl_af_7:
        case gpio_ioctl_af_8:
        case gpio_ioctl_af_9:
        case gpio_ioctl_af_10:
        case gpio_ioctl_af_11:
        case gpio_ioctl_af_12:
        case gpio_ioctl_af_13:
        case gpio_ioctl_af_14:
        case gpio_ioctl_af_15:
            sdk_gpio_set_alt(GPIO_port, GPIO_pin, gpio_ioctl - gpio_ioctl_af_0);
            break;
        default:
            return 1;
    }

    return 0;
}

int hal_gpio_write(GPIO_TypeDef *GPIO_port, uint32_t GPIO_pin, bool value) {
    if (sanity_check(GPIO_port, GPIO_pin) != 0) {
        return -1;
    }

    if (value) {
        sdk_gpio_bit_set(GPIO_port, GPIO_pin);
    } else {
        sdk_gpio_bit_reset(GPIO_port, GPIO_pin);
    }

    return 0;
}

bool hal_gpio_read(GPIO_TypeDef *GPIO_port, uint32_t GPIO_pin) {
    return sdk_gpio_read(GPIO_port, GPIO_pin);
}
