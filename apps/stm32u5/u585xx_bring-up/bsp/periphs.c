#include "bsp.h"
#include "hal_gpio.h"
#include "hal_i2c.h"

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

int bsp_init_periphs() {
    int err = 0;

    /* Init I2C1 */
    err = init_i2c(I2C1, BSP_I2C1_SDA_PORT, BSP_I2C1_SDA_PIN, BSP_I2C1_SCL_PORT, BSP_I2C1_SCL_PIN);
    ExitOnError(err);

    /* Init I2C2 */
    err = init_i2c(I2C2, BSP_I2C2_SDA_PORT, BSP_I2C2_SDA_PIN, BSP_I2C2_SCL_PORT, BSP_I2C2_SCL_PIN);
    ExitOnError(err);

exit:
    return err;
}