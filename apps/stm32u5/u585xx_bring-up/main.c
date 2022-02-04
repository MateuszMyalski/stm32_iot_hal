#include <stdlib.h>
#include <string.h>

#include "bsp.h"
#include "delay.h"
#include "gpio.h"
#include "logger.h"
#include "i2c.h"

int main() {
    Assert(bsp_init(), 0);
    uint8_t i2c_rx[2];
    // hal_i2c_master_read(I2C2, 0xBE, 0x20, i2c_rx, 2);
    hal_i2c_master_read(I2C2, 0xBE, 0x0F, i2c_rx, 1);

    // uint8_t i2c_tx[2] = {0x20, 0x84};
    // hal_i2c_master_write(I2C1, 0xBE, i2c_tx, 2);

    uint16_t rx_data = i2c_rx[1] << 8 | i2c_rx[0];
    LOG_INFO("Rxed value: %#x\r\n", rx_data);

    while (1) {
        bool r_value = !hal_gpio_read(BSP_USER_BUTTON_PORT, BSP_USER_BUTTON_PIN);
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, false);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, r_value);
        delay_ms(500);
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, true);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, r_value);
        delay_ms(300);
    }
}
