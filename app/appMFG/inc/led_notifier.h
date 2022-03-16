#ifndef APP_LED_NOTIFIER_H
#define APP_LED_NOTIFIER_H

/**
 * @brief Perform LED sequence to notify that the device is not in asssert.
 * @return (void)
 */
void led_notifier_idle(void);

/**
 * @brief Notify error by running LED seqence.
 * @return (void)
 */
void led_notifier_error_blink(void);

/**
 * @brief Notify device happy mood by running LED seqence.
 * @return (void)
 */
void led_notifier_happy_blink(void);

#endif
