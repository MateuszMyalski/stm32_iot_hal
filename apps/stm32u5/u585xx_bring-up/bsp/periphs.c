#include "bsp.h"
#include "gpio.h"
#include "i2c.h"

static int init_i2c2() {
    int err = 0;;

    /* SDA GPIO */
    // No internal pull-ups
    err = hal_gpio_open(BSP_I2C2_SDA_PORT);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_I2C2_SDA_PORT, BSP_I2C2_SDA_PIN, gpio_ioctl_output);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_I2C2_SDA_PORT, BSP_I2C2_SDA_PIN, gpio_ioctl_alternate);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_I2C2_SDA_PORT, BSP_I2C2_SDA_PIN, gpio_ioctl_open_drain);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_I2C2_SDA_PORT, BSP_I2C2_SDA_PIN, gpio_ioctl_very_high_speed);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_I2C2_SDA_PORT, BSP_I2C2_SDA_PIN, gpio_ioctl_af_4);
    ExitOnError(err);

    /* SCL GPIO */
    // No internal pull-ups
    err = hal_gpio_open(BSP_I2C2_SCL_PORT);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_I2C2_SCL_PORT, BSP_I2C2_SCL_PIN, gpio_ioctl_output);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_I2C2_SCL_PORT, BSP_I2C2_SCL_PIN, gpio_ioctl_alternate);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_I2C2_SCL_PORT, BSP_I2C2_SCL_PIN, gpio_ioctl_open_drain);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_I2C2_SCL_PORT, BSP_I2C2_SCL_PIN, gpio_ioctl_very_high_speed);
    ExitOnError(err);

    err = hal_gpio_ioctl(BSP_I2C2_SCL_PORT, BSP_I2C2_SCL_PIN, gpio_ioctl_af_4);
    ExitOnError(err);

    err = hal_i2c_open(I2C2, I2C_mode_master);
    ExitOnError(err);

exit:
    return err;
}

int bsp_init_periphs() {
    int err = 0;

    /* Init I2C2 */
    err = init_i2c2();
    ExitOnError(err);

exit:
    return err;
}