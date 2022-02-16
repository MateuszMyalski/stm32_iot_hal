#ifndef BSP_HPP
#define BSP_HPP

#define BSP_RED_LED_PORT GPIOH
#define BSP_RED_LED_PIN 6U

#define BSP_GREEN_LED_PORT GPIOH
#define BSP_GREEN_LED_PIN 7U

#define BSP_USER_BUTTON_PORT GPIOC
#define BSP_USER_BUTTON_PIN 13U

#define BSP_I2C2_SDA_PORT GPIOH
#define BSP_I2C2_SDA_PIN 5U

#define BSP_I2C2_SCL_PORT GPIOH
#define BSP_I2C2_SCL_PIN 4U

#define BSP_I2C1_SDA_PORT GPIOB
#define BSP_I2C1_SDA_PIN 9U

#define BSP_I2C1_SCL_PORT GPIOB
#define BSP_I2C1_SCL_PIN 8U

// Switches either USART2 or SPI1 to CN3:STMOD+1 and CN4:PMOD connectors
#define BSP_STMOD1_USART2_SPI1_SEL_PORT GPIOH
#define BSP_STMOD1_USART2_SPI1_SEL_PIN  13u

// Switches either USART3 or SPI3 to CN2:STMOD+2 connector
#define BSP_STMOD1_USART3_SPI3_SEL_PORT GPIOH
#define BSP_STMOD1_USART3_SPI3_SEL_PIN  15u

#define BSP_USART1_RX_PORT GPIOA
#define BSP_USART1_RX_PIN  10u

#define BSP_USART1_TX_PORT GPIOA
#define BSP_USART1_TX_PIN  9u

#define BSP_USART2_RX_PORT GPIOA
#define BSP_USART2_RX_PIN  3u

#define BSP_USART2_TX_PORT GPIOA
#define BSP_USART2_TX_PIN  2u

#define BSP_USART3_RX_PORT PORTD
#define BSP_USART3_RX_PIN  9u

#define BSP_USART3_TX_PORT PORTD
#define BSP_USART3_TX_PIN  8u

#define BSP_UART4_RX_PORT
#define BSP_UART4_RX_PIN

#define BSP_UART4_TX_PORT
#define BSP_UART4_TX_PIN

#define BSP_UART5_RX_PORT
#define BSP_UART5_RX_PIN

#define BSP_UART5_TX_PORT
#define BSP_UART5_TX_PIN

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
int bsp_init(void);

/**
 * @brief Initalize all GPIOS used for leds
 * @return 0 - on success, 1 - on error
 */
int bsp_init_led(void);

/**
 * @brief Initalize all peripherials
 * @return 0 - on success, 1 - on error
 */
int bsp_init_periphs(void);

#endif
