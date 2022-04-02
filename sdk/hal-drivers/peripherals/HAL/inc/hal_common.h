#ifndef HAL_COMMON_H
#define HAL_COMMON_H

#include <stddef.h>

#include "stm32u585xx.h"
#include "stm32u5xx.h"

typedef enum {
    HAL_NO_ERR              = 0,
    HAL_ERR_PARAMS          = -1,
    HAL_ERR_NOT_IMPLEMENTED = -2,
} hal_err_t;

#endif
