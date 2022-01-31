#include "gpio.h"
#include <stdbool.h>
#include "hal_common.h"

#define GPIO_REG_SIZE 0x00400U
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

    // Translate port A - I -> 0 - 9
    uint32_t port_idx = (uint32_t)GPIO_port - (uint32_t)GPIOA_BASE;
    port_idx /= GPIO_REG_SIZE;

    // Enable AHB bus
    SET_BIT(RCC->AHB2ENR1, 1 << port_idx);

    return 0;
}

int hal_gpio_close(GPIO_TypeDef *GPIO_port) {
    if (sanity_check(GPIO_port, 0) != 0) {
        return -1;
    }

    // Translate port A - I -> 0 - 9
    uint32_t port_idx = (uint32_t)GPIO_port - (uint32_t)GPIOA_BASE;
    port_idx /= GPIO_REG_SIZE;

    // Enable AHB bus
    SET_BIT(RCC->AHB2RSTR1, 1 << port_idx);

    return 0;
}

int hal_gpio_ioctl(GPIO_TypeDef *GPIO_port, uint32_t GPIO_pin, gpio_ioctl_t gpio_ioctl) {
    if (sanity_check(GPIO_port, GPIO_pin) != 0) {
        return -1;
    }

    switch (gpio_ioctl) {
        case gpio_ioctl_digital_input: {
            int MODER_pos = GPIO_pin << 1;

            CLEAR_BIT(GPIO_port->MODER, 2UL << MODER_pos);
            CLEAR_BIT(GPIO_port->MODER, 1UL << MODER_pos);

            break;
        }
        case gpio_ioctl_output: {
            int MODER_pos = GPIO_pin << 1;

            CLEAR_BIT(GPIO_port->MODER, 2UL << MODER_pos);
            SET_BIT(GPIO_port->MODER, 1UL << MODER_pos);

            break;
        }
        case gpio_ioctl_analog_input: {
            int MODER_pos = GPIO_pin << 1;

            SET_BIT(GPIO_port->MODER, 2UL << MODER_pos);
            SET_BIT(GPIO_port->MODER, 1UL << MODER_pos);

            break;
        }
        case gpio_ioctl_alternate: {
            int MODER_pos = GPIO_pin << 1;

            SET_BIT(GPIO_port->MODER, 2UL << MODER_pos);
            CLEAR_BIT(GPIO_port->MODER, 1UL << MODER_pos);

            break;
        }
        case gpio_ioctl_push_pull:
            CLEAR_BIT(GPIO_port->OTYPER, GPIO_pin);
            break;
        case gpio_ioctl_open_drain:
            SET_BIT(GPIO_port->OTYPER, GPIO_pin);
            break;
        case gpio_ioctl_low_speed: {
            int OSPEEDR_pos = GPIO_pin << 1;

            CLEAR_BIT(GPIO_port->OSPEEDR, 2UL << OSPEEDR_pos);
            CLEAR_BIT(GPIO_port->OSPEEDR, 1UL << OSPEEDR_pos);
            break;
        }
        case gpio_ioctl_medium_speed: {
            int OSPEEDR_pos = GPIO_pin << 1;

            CLEAR_BIT(GPIO_port->OSPEEDR, 2UL << OSPEEDR_pos);
            SET_BIT(GPIO_port->OSPEEDR, 1UL << OSPEEDR_pos);
            break;
        }
        case gpio_ioctl_high_speed: {
            int OSPEEDR_pos = GPIO_pin << 1;

            SET_BIT(GPIO_port->OSPEEDR, 2UL << OSPEEDR_pos);
            CLEAR_BIT(GPIO_port->OSPEEDR, 1UL << OSPEEDR_pos);
            break;
        }
        case gpio_ioctl_very_high_speed: {
            int OSPEEDR_pos = GPIO_pin << 1;

            SET_BIT(GPIO_port->OSPEEDR, 2UL << OSPEEDR_pos);
            SET_BIT(GPIO_port->OSPEEDR, 1UL << OSPEEDR_pos);
            break;
        }
        case gpio_ioctl_no_pull: {
            int PUPDR_pos = GPIO_pin << 1;

            CLEAR_BIT(GPIO_port->PUPDR, 2UL << PUPDR_pos);
            CLEAR_BIT(GPIO_port->PUPDR, 1UL << PUPDR_pos);
            break;
        }
        case gpio_ioctl_pull_up: {
            int PUPDR_pos = GPIO_pin << 1;

            CLEAR_BIT(GPIO_port->PUPDR, 2UL << PUPDR_pos);
            SET_BIT(GPIO_port->PUPDR, 1UL << PUPDR_pos);
            break;
        }
        case gpio_ioctl_pull_down: {
            int PUPDR_pos = GPIO_pin << 1;

            SET_BIT(GPIO_port->PUPDR, 2UL << PUPDR_pos);
            CLEAR_BIT(GPIO_port->PUPDR, 1UL << PUPDR_pos);
            break;
        }
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
        case gpio_ioctl_af_15: {
            int AFR_idx = GPIO_pin < 7 ? 0 : 1;
            int AFR_pos = (GPIO_pin << 2) % 32;
            uint32_t AFR_msk = 0x0FUL << AFR_pos;
            int AFSELy = gpio_ioctl - gpio_ioctl_af_0;  // Translate offseted enum value

            MODIFY_REG(GPIO_port->AFR[AFR_idx], AFR_msk, AFSELy << AFR_pos);
            break;
        }

        default:
            return 1;
            break;
    }
    return 0;
}

int hal_gpio_write(GPIO_TypeDef *GPIO_port, uint32_t GPIO_pin, bool value) {
    if (sanity_check(GPIO_port, GPIO_pin) != 0) {
        return -1;
    }

    int BRR_pos = GPIO_pin + 16;
    int BSR_pos = GPIO_pin;

    // BSSR is 32 bit register divided in half
    // LSB for BS (Bit Set) and MSB for BR (Bit Reset)
    if (value) {
        SET_BIT(GPIO_port->BSRR, 1UL << BSR_pos);
        CLEAR_BIT(GPIO_port->BSRR, 1UL << BRR_pos);
    } else {
        CLEAR_BIT(GPIO_port->BSRR, 1UL << BSR_pos);
        SET_BIT(GPIO_port->BSRR, 1UL << BRR_pos);
    }

    return 0;
}

bool hal_gpio_read(GPIO_TypeDef *GPIO_port, uint32_t GPIO_pin) {
    // No sanity check

    return READ_BIT(GPIO_port->IDR, 1UL << GPIO_pin);
}
