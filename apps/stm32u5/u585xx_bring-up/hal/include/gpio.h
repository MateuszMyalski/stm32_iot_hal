#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include "hal_common.h"
typedef enum {
    gpio_ioctl_digital_input,
    gpio_ioctl_output,
    gpio_ioctl_analog_input,
    gpio_ioctl_alternate,
    gpio_ioctl_push_pull,
    gpio_ioctl_open_drain,
    gpio_ioctl_low_speed,
    gpio_ioctl_medium_speed,
    gpio_ioctl_high_speed,
    gpio_ioctl_very_high_speed,
    gpio_ioctl_no_pull,
    gpio_ioctl_pull_up,
    gpio_ioctl_pull_down,
    gpio_ioctl_af_0,
    gpio_ioctl_af_1,
    gpio_ioctl_af_2,
    gpio_ioctl_af_3,
    gpio_ioctl_af_4,
    gpio_ioctl_af_5,
    gpio_ioctl_af_6,
    gpio_ioctl_af_7,
    gpio_ioctl_af_8,
    gpio_ioctl_af_9,
    gpio_ioctl_af_10,
    gpio_ioctl_af_11,
    gpio_ioctl_af_12,
    gpio_ioctl_af_13,
    gpio_ioctl_af_14,
    gpio_ioctl_af_15,
} gpio_ioctl_t;

/**
 * @brief Enables the AHB bus on selected GPIO port
 * @param GPIO_port - CMSIS GPIOx port
 * @return 0 - on success, -1 - on error
 */
int hal_gpio_open(GPIO_TypeDef *GPIO_port);

/**
 * @brief Resets the AHB bus on selected GPIO port
 * @param GPIO_port - CMSIS GPIOx port
 * @return 0 - on success, -1 - on error
 */
int hal_gpio_close(GPIO_TypeDef *GPIO_port);

/**
 * @brief Sets mode/type of pin in selected GPIO port
 * @param GPIO_port - CMSIS GPIOx port
 * @param GPIO_pin - pin number
 * @param gpio_ioctl - enumaration of function to set for selected pin
 * @return 0 - on sucecss, -1 - on error, 1 - on not implemented
 */
int hal_gpio_ioctl(GPIO_TypeDef *GPIO_port, uint32_t GPIO_pin, gpio_ioctl_t gpio_ioctl);

/**
 * @brief Set value on data output register on selected GPIO port pin
 * @param GPIO_port - CMSIS GPIOx port
 * @param GPIO_pin - pin number
 * @param value - 0/1 - Digital value
 * @return 0 - on success, -1 - on error
 */
int hal_gpio_write(GPIO_TypeDef *GPIO_port, uint32_t GPIO_pin, bool value);

/**
 * @brief Read value on data input register on selected GPIO port pin
 * @param GPIO_port - CMSIS GPIOx port
 * @param GPIO_pin - pin number
 * @return 0/1 - Digital value present on selected pin
 */
bool hal_gpio_read(GPIO_TypeDef *GPIO_port, uint32_t GPIO_pin);

#endif
