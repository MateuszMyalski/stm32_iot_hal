
#include "bsp_utils.h"


int bsp_ioctl(BSP_connector connector, BSP_periph_sel peripheral) {

    if (BSP_PMOD == connector) {

        switch(peripheral) {

            case BSP_PMOD_USART2:
                hal_gpio_write(BSP_PMOD_PERIPH_SEL_PORT, BSP_PMOD_PERIPH_SEL_PIN, true);
                break;

            case BSP_PMOD_SPI1:
                hal_gpio_write(BSP_PMOD_PERIPH_SEL_PORT, BSP_PMOD_PERIPH_SEL_PIN, false);
                break;
            
            default:
                return HAL_ERR_PARAMS;
        }
    }

    return HAL_NO_ERR;
}