#ifndef BSP_BSP_H
#define BSP_BSP_H

#include "hal_common.h"

#define BSP_RED_LED_PORT GPIOH
#define BSP_RED_LED_PIN  6U

#define BSP_GREEN_LED_PORT GPIOH
#define BSP_GREEN_LED_PIN  7U

#define BSP_USER_BUTTON_PORT GPIOC
#define BSP_USER_BUTTON_PIN  13U

#define BSP_I2C2_SDA_PORT GPIOH
#define BSP_I2C2_SDA_PIN  5U

#define BSP_I2C2_SCL_PORT GPIOH
#define BSP_I2C2_SCL_PIN  4U

#define BSP_I2C1_SDA_PORT GPIOB
#define BSP_I2C1_SDA_PIN  9U

#define BSP_I2C1_SCL_PORT GPIOB
#define BSP_I2C1_SCL_PIN  8U

#define BSP_EEPROM_I2C            I2C2
#define BSP_EEPROM_ADDR           0xADU
#define BSP_EEPROM_WRITE_DELAY_MS 6UL

#define BSP_HTS221_I2C  I2C2
#define BSP_HTS221_ADDR 0xBEUL

// Switches either USART2 or SPI1 to CN3:STMOD+1 and CN4:PMOD connectors
#define BSP_PMOD_PERIPH_SEL_PORT GPIOH
#define BSP_PMOD_PERIPH_SEL_PIN  13U

// Switches either USART3 or SPI3 to CN2:STMOD+2 connector
#define BSP_STMOD1_USART3_SPI3_SEL_PORT GPIOH
#define BSP_STMOD1_USART3_SPI3_SEL_PIN  15U

// USART1:3 IOs
#define BSP_USART1_IO_PORT GPIOA
#define BSP_USART1_RX_PIN  10U
#define BSP_USART1_TX_PIN  9U

#define BSP_USART2_IO_PORT GPIOA
#define BSP_USART2_RX_PIN  3U
#define BSP_USART2_TX_PIN  2U

#define BSP_USART3_IO_PORT PORTD
#define BSP_USART3_RX_PIN  9U
#define BSP_USART3_TX_PIN  8U

// UART 4:5 IOs to be implemented
#define BSP_UART4_IO_PORT
#define BSP_UART4_TX_PIN
#define BSP_UART5_RX_PIN

#define BSP_UART5_IO_PORT
#define BSP_UART5_TX_PORT
#define BSP_UART5_TX_PIN

/**
 * @brief Defines peripherals available on board connectors
 */
typedef enum {
    BSP_PMOD_USART2, /* Enabless USART2 signals on CN4-PMOD connector */
    BSP_PMOD_SPI1    /* Enabless SPI1   signals on CN4-PMOD connector */
} BSP_periph_sel;

/**
 * @brief Defines configurable connectors available on board
 */
typedef enum {
    BSP_PMOD     /* CN4-PMOD connector */
} BSP_connector;

/**
 * @brief Initialize periphs on EVB
 * @return 0 - on success, -1 - on error
 */
int bsp_init(void);

/**
 * @brief Initalize all GPIOS used for leds
 * @return 0 - on success, -1 - on error
 */
int bsp_init_led(void);

/**
 * @brief Initalize all peripherials
 * @return 0 - on success, -1 - on error
 */
int bsp_init_periphs(void);

/**
 * @brief Enables selected peripheral on selected board connector
 */
int bsp_ioctl(BSP_connector connector, BSP_periph_sel peripheral);

#endif
