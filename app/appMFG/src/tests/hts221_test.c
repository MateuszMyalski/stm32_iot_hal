#include "hts221.h"

#include <stdbool.h>

#include "bsp.h"
#include "led_notifier.h"
#include "logger.h"

static hts221_ctx_t hts221_ctx = {0};

static bool hts221_test_who_am_i(void);
static bool hts221_test_power_on(void);

// TODO Use real testing framework lanuched from CLI
void hts221_test(void) {
    hts221_err_t err = HTS221_NO_ERR;

    err = hts221_init(&hts221_ctx, BSP_HTS221_ADDR, BSP_HTS221_I2C);
    if (err != HTS221_NO_ERR) {
        led_notifier_error_blink();
        return;
    }

    bool test_passed = false;

    test_passed = hts221_test_who_am_i();
    if (!test_passed) {
        LOG_ERR("HTS221 Test who am i - FAILED!\r\n");
        led_notifier_error_blink();
        return;
    }

    LOG_SUCCESS("HTS221 Test who am i - PASSED!\r\n");

    test_passed = hts221_test_power_on();
    if (!test_passed) {
        LOG_ERR("HTS221 Test Power on - FAILED!\r\n");
        led_notifier_error_blink();
        return;
    }

    LOG_SUCCESS("HTS221 Test Power on - PASSED!\r\n");
}

static bool hts221_test_who_am_i(void) {
    uint8_t buffer   = 0;
    hts221_err_t err = HTS221_NO_ERR;

    err = hts221_read_who_am_i(&hts221_ctx, &buffer);
    if (err != HTS221_NO_ERR) {
        led_notifier_error_blink();
        return false;
    }

    return buffer == 0xBC;
}

static bool hts221_test_power_on(void) {
    uint8_t buffer        = 0;
    uint8_t initial_state = 0;
    hts221_err_t err      = HTS221_NO_ERR;

    /* Read initial state */
    err = hts221_read_ctrl_reg1(&hts221_ctx, &initial_state);
    if (err != HTS221_NO_ERR) {
        led_notifier_error_blink();
        return false;
    }

    /* Turn on the device */
    initial_state |= HTS221_CTRL_REG1_PD;

    err = hts221_set_ctrl_reg1(&hts221_ctx, initial_state);
    if (err != HTS221_NO_ERR) {
        led_notifier_error_blink();
        return false;
    }

    /* Read written value */
    buffer = 0x0;

    err = hts221_read_ctrl_reg1(&hts221_ctx, &buffer);
    if (err != HTS221_NO_ERR) {
        led_notifier_error_blink();
        return false;
    }

    return buffer == initial_state;
}
