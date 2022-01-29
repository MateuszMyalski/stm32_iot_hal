#ifndef BSP_HPP
#define BSP_HPP

#define BSP_RED_LED_PORT GPIOH
#define BSP_RED_LED_PIN 6

#define BSP_GREEN_LED_PORT GPIOH
#define BSP_GREEN_LED_PIN 7

#define BSP_USER_BUTTON_PORT GPIOC
#define BSP_USER_BUTTON_PIN 13

#define ExitOnError(x)  \
    do {                \
        if (0 != (x)) { \
            goto exit;  \
        }               \
    } while (0);

#define Assert(_expression, _expected)      \
    do {                                    \
        if ((_expression) != (_expected)) { \
            while (1)                       \
                ;                           \
        }                                   \
    } while (0);

/**
 * @brief Initialize periphs on EVB
 * @return 0 - on success, 1 - on error
 */
int bsp_init();

/**
 * @brief Initalize all GPIOS used for leds
 * @return 0 - on success, 1 - on error
 */
int bsp_init_led();

#endif
