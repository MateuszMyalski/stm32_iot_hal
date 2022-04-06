
#ifndef BSP_UTILS
#define BSP_UTILS

#include "hal_gpio.h"
#include "bsp.h"

/**
 * @brief Enables selected peripheral on selected board connector
 */
int bsp_ioctl(BSP_connector connector, BSP_periph_sel peripheral);

#endif