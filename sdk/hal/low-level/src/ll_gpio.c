#include "ll_gpio.h"

#define GPIO_REG_SIZE 0x00400U

void ll_gpio_enable_AHB(GPIO_TypeDef *port) {
    uint32_t port_idx = (uint32_t)port - (uint32_t)GPIOA_BASE;
    port_idx /= GPIO_REG_SIZE;

    SET_BIT(RCC->AHB2ENR1, 1 << port_idx);
}

void ll_gpio_disable_AHB(GPIO_TypeDef *port) {
    uint32_t port_idx = (uint32_t)port - (uint32_t)GPIOA_BASE;
    port_idx /= GPIO_REG_SIZE;

    CLEAR_BIT(RCC->AHB2ENR1, 1 << port_idx);
}

inline void ll_gpio_mode_digital_in(GPIO_TypeDef *port, uint32_t pin) {
    int MODER_idx = pin << 1;

    CLEAR_BIT(port->MODER, 2UL << MODER_idx);
    CLEAR_BIT(port->MODER, 1UL << MODER_idx);
}

inline void ll_gpio_mode_analog_in(GPIO_TypeDef *port, uint32_t pin) {
    int MODER_idx = pin << 1;

    SET_BIT(port->MODER, 2UL << MODER_idx);
    SET_BIT(port->MODER, 1UL << MODER_idx);
}

inline void ll_gpio_mode_out(GPIO_TypeDef *port, uint32_t pin) {
    int MODER_idx = pin << 1;

    CLEAR_BIT(port->MODER, 2UL << MODER_idx);
    SET_BIT(port->MODER, 1UL << MODER_idx);
}

inline void ll_gpio_mode_alt(GPIO_TypeDef *port, uint32_t pin) {
    int MODER_idx = pin << 1;

    SET_BIT(port->MODER, 2UL << MODER_idx);
    CLEAR_BIT(port->MODER, 1UL << MODER_idx);
}

inline void ll_gpio_type_pp(GPIO_TypeDef *port, uint32_t pin) {
    CLEAR_BIT(port->OTYPER, 1UL << pin);
}

inline void ll_gpio_type_od(GPIO_TypeDef *port, uint32_t pin) {
    SET_BIT(port->OTYPER, 1UL << pin);
}

inline void ll_gpio_speed_low(GPIO_TypeDef *port, uint32_t pin) {
    int OSPEEDR_idx = pin << 1;

    CLEAR_BIT(port->OSPEEDR, 2UL << OSPEEDR_idx);
    CLEAR_BIT(port->OSPEEDR, 1UL << OSPEEDR_idx);
}

inline void ll_gpio_speed_medium(GPIO_TypeDef *port, uint32_t pin) {
    int OSPEEDR_idx = pin << 1;

    CLEAR_BIT(port->OSPEEDR, 2UL << OSPEEDR_idx);
    SET_BIT(port->OSPEEDR, 1UL << OSPEEDR_idx);
}

inline void ll_gpio_speed_high(GPIO_TypeDef *port, uint32_t pin) {
    int OSPEEDR_idx = pin << 1;

    SET_BIT(port->OSPEEDR, 2UL << OSPEEDR_idx);
    CLEAR_BIT(port->OSPEEDR, 1UL << OSPEEDR_idx);
}

inline void ll_gpio_speed_very_high(GPIO_TypeDef *port, uint32_t pin) {
    int OSPEEDR_idx = pin << 1;

    SET_BIT(port->OSPEEDR, 2UL << OSPEEDR_idx);
    SET_BIT(port->OSPEEDR, 1UL << OSPEEDR_idx);
}

inline void ll_gpio_no_pull(GPIO_TypeDef *port, uint32_t pin) {
    int PUPDR_idx = pin << 1;

    CLEAR_BIT(port->PUPDR, 2UL << PUPDR_idx);
    CLEAR_BIT(port->PUPDR, 1UL << PUPDR_idx);
}

inline void ll_gpio_pull_up(GPIO_TypeDef *port, uint32_t pin) {
    int PUPDR_idx = pin << 1;

    CLEAR_BIT(port->PUPDR, 2UL << PUPDR_idx);
    SET_BIT(port->PUPDR, 1UL << PUPDR_idx);
}

inline void ll_gpio_pull_down(GPIO_TypeDef *port, uint32_t pin) {
    int PUPDR_idx = pin << 1;

    SET_BIT(port->PUPDR, 2UL << PUPDR_idx);
    CLEAR_BIT(port->PUPDR, 1UL << PUPDR_idx);
}

inline void ll_gpio_set_alt(GPIO_TypeDef *port, uint32_t pin, uint32_t alt_idx) {
    int AFR_idx      = pin < 7 ? 0 : 1;
    int AFR_pos      = (pin << 2) % 32;
    uint32_t AFR_msk = 0x0FUL << AFR_idx;

    MODIFY_REG(port->AFR[AFR_idx], AFR_msk, alt_idx << AFR_pos);
}

inline void ll_gpio_bit_set(GPIO_TypeDef *port, uint32_t pin) {
    int BRR_pos = pin + 16;
    int BSR_pos = pin;

    SET_BIT(port->BSRR, 1UL << BSR_pos);
    CLEAR_BIT(port->BSRR, 1UL << BRR_pos);
}

inline void ll_gpio_bit_reset(GPIO_TypeDef *port, uint32_t pin) {
    int BRR_pos = pin + 16;
    int BSR_pos = pin;

    CLEAR_BIT(port->BSRR, 1UL << BSR_pos);
    SET_BIT(port->BSRR, 1UL << BRR_pos);
}

inline bool ll_gpio_read(GPIO_TypeDef *port, uint32_t pin) {
    return READ_BIT(port->IDR, 1UL << pin);
}
