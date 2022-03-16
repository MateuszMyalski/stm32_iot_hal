#ifndef BSP_BSP_H
#define BSP_BSP_H

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

#endif