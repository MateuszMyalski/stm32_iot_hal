#ifndef HAL_SDK_GPIO_H
#define HAL_SDK_GPIO_H
#include <stdbool.h>
#include "stm32u5xx.h"
#include "stm32u585xx.h"

void sdk_gpio_enable_AHB(GPIO_TypeDef *port);
void sdk_gpio_disable_AHB(GPIO_TypeDef *port);

void sdk_gpio_mode_digital_in(GPIO_TypeDef *port, uint32_t pin);
void sdk_gpio_mode_analog_in(GPIO_TypeDef *port, uint32_t pin);
void sdk_gpio_mode_out(GPIO_TypeDef *port, uint32_t pin);
void sdk_gpio_mode_alt(GPIO_TypeDef *port, uint32_t pin);

void sdk_gpio_type_pp(GPIO_TypeDef *port, uint32_t pin);
void sdk_gpio_type_od(GPIO_TypeDef *port, uint32_t pin);

void sdk_gpio_speed_low(GPIO_TypeDef *port, uint32_t pin);
void sdk_gpio_speed_medium(GPIO_TypeDef *port, uint32_t pin);
void sdk_gpio_speed_high(GPIO_TypeDef *port, uint32_t pin);
void sdk_gpio_speed_very_high(GPIO_TypeDef *port, uint32_t pin);

void sdk_gpio_no_pull(GPIO_TypeDef *port, uint32_t pin);
void sdk_gpio_pull_up(GPIO_TypeDef *port, uint32_t pin);
void sdk_gpio_pull_down(GPIO_TypeDef *port, uint32_t pin);

void sdk_gpio_set_alt(GPIO_TypeDef *port, uint32_t pin, uint32_t alt_idx);

void sdk_gpio_bit_reset(GPIO_TypeDef *port, uint32_t pin);
void sdk_gpio_bit_set(GPIO_TypeDef *port, uint32_t pin);

bool sdk_gpio_read(GPIO_TypeDef *port, uint32_t pin);

#endif
