#ifndef APP_FACTORY_RESET_H
#define APP_FACTORY_RESET_H

/**
 * @brief Perform all necessary stages to revert device to the factory state.
 * @return (void)
 */
void factory_reset_handle(void);

/**
 * @brief Check if factory reset should be perforemd.
 * @return true - factory reset should be performed,
 *         false - no factory reset trigger found
 */
bool factory_reset_check_trigger(void);

#endif
