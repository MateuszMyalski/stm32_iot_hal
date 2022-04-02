#include "bsp.h"
#include "ee_storage.h"
#include "eeprom_map.h"
#include "factory_reset.h"
#include "hts221_test.h"
#include "led_notifier.h"
#include "logger.h"

// uint8_t rev8(uint8_t value) {
//     uint32_t out = 0x0;
//     for (int i = 0; i < 8; i++) {
//         out |= (value & 0b1) << (7 - i);
//         value >>= 1;
//     }

//     return out;
// }

// uint32_t rev32(uint32_t value) {
//     uint32_t out = 0x0;
//     for (int i = 0; i < 32; i++) {
//         out |= (value & 0b1) << (31 - i);
//         value >>= 1;
//     }

//     return out;
// }

// uint32_t Crc32(uint32_t Crc, uint32_t Data) {
//     int i;

//     uint32_t tmp = 0x0;
//     tmp |= rev8(Data);
//     tmp |= rev8(Data >> 8) << 8;
//     tmp |= rev8(Data >> 16) << 16;
//     tmp |= rev8(Data >> 24) << 24;
//     Data = tmp;

//     Crc = Crc ^ Data;

//     for (i = 0; i < 32; i++)
//         if (Crc & 0x80000000)
//             Crc = (Crc << 1) ^ 0x04C11DB7;  // Polynomial used in STM32
//         else
//             Crc = (Crc << 1);

//     return (Crc);
// }

// uint32_t crc_data(const uint8_t* data_in, size_t size) {

//     uint32_t prev_crc = 0xFFFFFFFF;
//     size_t n_words = size / sizeof(uint32_t);
//     for (size_t i = 0; i < n_words; i++) {
//         uint8_t *v4 = data_in + i * sizeof(uint32_t);
//         uint32_t i32 = v4[3] | (v4[2] << 8) | (v4[1] << 16) | (v4[0] << 24);
//         prev_crc = Crc32(prev_crc, i32);
//     }

//     size_t n_bytes = size - (n_words * sizeof(uint32_t));
//     if(0 < n_bytes){
//         uint32_t i32 = 0x0;
//         uint8_t *v4 = data_in + n_words * sizeof(uint32_t);
//         for(size_t i = 0; i < n_bytes; i++) {
//             i32 |= v4[i] << (8 * i);
//         }
//         prev_crc = Crc32(prev_crc, i32);
//     }

//     return rev32(prev_crc);
// }

int main() {
    bsp_init();
    init_ee_storage();

    LOG_INFO("Build: " BUILD_USER "\r\n");

    if (factory_reset_check_trigger()) {
        LOG_WARN("Factory reset triggered!\r\n");
        factory_reset_handle();
        led_notifier_happy_blink();
    }

    hts221_test();

    part_device_info_t device_info = {};
    ee_storage_get_device_info(&device_info);

    while (1) {
        LOG_INFO("Idle state...\r\n");
        led_notifier_idle();
    }
}
