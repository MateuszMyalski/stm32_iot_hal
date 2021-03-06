#include "hal_usart.h"
#include "hal_gpio.h"
#include "hal_i2c.h"

#include "bsp_utils.h"
#include "utils.h"
#include "bsp.h"


static int init_i2c(I2C_TypeDef* I2C, GPIO_TypeDef* I2C_SDA_port, uint32_t I2C_SDA_pin, GPIO_TypeDef* I2C_SCL_port,
                    uint32_t I2C_SCL_pin) {
    int err = 0;

    /* SDA GPIO */
    err = hal_gpio_open(I2C_SDA_port);
    ExitOnError(err);

    err = hal_gpio_ioctl(I2C_SDA_port, I2C_SDA_pin, gpio_ioctl_af_4);
    ExitOnError(err);

    err = hal_gpio_ioctl(I2C_SDA_port, I2C_SDA_pin, gpio_ioctl_alternate);
    ExitOnError(err);

    err = hal_gpio_ioctl(I2C_SDA_port, I2C_SDA_pin, gpio_ioctl_open_drain);
    ExitOnError(err);

    err = hal_gpio_ioctl(I2C_SDA_port, I2C_SDA_pin, gpio_ioctl_very_high_speed);
    ExitOnError(err);

    /* SCL GPIO */
    // No internal pull-ups
    err = hal_gpio_open(I2C_SCL_port);
    ExitOnError(err);

    err = hal_gpio_ioctl(I2C_SCL_port, I2C_SCL_pin, gpio_ioctl_af_4);
    ExitOnError(err);

    err = hal_gpio_ioctl(I2C_SCL_port, I2C_SCL_pin, gpio_ioctl_alternate);
    ExitOnError(err);

    err = hal_gpio_ioctl(I2C_SCL_port, I2C_SCL_pin, gpio_ioctl_open_drain);
    ExitOnError(err);

    err = hal_gpio_ioctl(I2C_SCL_port, I2C_SCL_pin, gpio_ioctl_very_high_speed);
    ExitOnError(err);

    /* I2C peripherial */
    err = hal_i2c_open(I2C, I2C_mode_master, I2C_speed_100kHz);
    ExitOnError(err);

exit:
    return err;
}


static int init_usart(USART_TypeDef *USART, GPIO_TypeDef *io_port, uint32_t tx_pin, uint32_t rx_pin, USART_opmode mode) {

    uint32_t timeout = 1152;
    int err = 0;

    err = hal_gpio_open(io_port);
    ExitOnError(err);

    err = hal_gpio_ioctl(io_port, tx_pin, gpio_ioctl_af_7);
    ExitOnError(err);
    err = hal_gpio_ioctl(io_port, tx_pin, gpio_ioctl_alternate);
    ExitOnError(err);
    err = hal_gpio_ioctl(io_port, tx_pin, gpio_ioctl_push_pull);
    ExitOnError(err);

    err = hal_gpio_ioctl(io_port, rx_pin, gpio_ioctl_af_7);
    ExitOnError(err);
    err = hal_gpio_ioctl(io_port, rx_pin, gpio_ioctl_alternate);
    ExitOnError(err);
    err = hal_gpio_ioctl(io_port, rx_pin, gpio_ioctl_push_pull);
    ExitOnError(err);

    err = hal_usart_open(USART2, USART_BAUD_115200, mode);
    err = hal_usart_ioctl(USART2, USART_IOCTL_PERIPH_TIMEOUT, (void *)&timeout);
    ExitOnError(err);

exit:
    return err;
}

int bsp_init_periphs() {
    int err = 0;

    /* Init I2C1 */
    err = init_i2c(I2C1, BSP_I2C1_SDA_PORT, BSP_I2C1_SDA_PIN, BSP_I2C1_SCL_PORT, BSP_I2C1_SCL_PIN);
    ExitOnError(err);

    /* Init I2C2 */
    err = init_i2c(I2C2, BSP_I2C2_SDA_PORT, BSP_I2C2_SDA_PIN, BSP_I2C2_SCL_PORT, BSP_I2C2_SCL_PIN);
    ExitOnError(err);

    err = init_usart(USART2, BSP_USART2_IO_PORT, BSP_USART2_TX_PIN, BSP_USART2_RX_PIN, USART_OPMODE_NORMAL);

    err = hal_gpio_open(BSP_PMOD_PERIPH_SEL_PORT);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_PMOD_PERIPH_SEL_PORT, BSP_PMOD_PERIPH_SEL_PIN, gpio_ioctl_output);
    ExitOnError(err);
    err = hal_gpio_ioctl(BSP_PMOD_PERIPH_SEL_PORT, BSP_PMOD_PERIPH_SEL_PIN, gpio_ioctl_pull_up);
    ExitOnError(err);
    err = hal_gpio_ioctl(BSP_PMOD_PERIPH_SEL_PORT, BSP_PMOD_PERIPH_SEL_PIN, gpio_ioctl_open_drain);
    ExitOnError(err);

    // switch USART2 output PMOD connector
    bsp_ioctl(BSP_PMOD, BSP_PMOD_USART2);

exit:
    return err;
}
