#include "eeprom.h"

int eeprom_M4256_D_init(eeprom_t *eeprom, tx_data_cb_t tx_data_cb, rx_data_cb_t rx_data_cb) {
    if (NULL == eeprom) {
        return -1;
    }

    eeprom->device = M24256_D;
    eeprom->page_size = 64;
    eeprom->memory_size = 32000;  // 256Kbit - 32Kbyte - 32000 bytes
    eeprom->tx_data_cb = tx_data_cb;
    eeprom->rx_data_cb = rx_data_cb;

    return 0;
}

