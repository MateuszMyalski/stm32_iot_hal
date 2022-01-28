#define LL_CANARY_REGISTER_SET(x) \
    do {                          \
        __asm("LDR  r0, = " #x);  \
    } while (0);

void BusFault_Handler(void) {
    while (1) {
        LL_CANARY_REGISTER_SET(0xAAAABBBB);
        // Hang the device
    }
}

void HardFault_Handler(void) {
    while (1) {
        LL_CANARY_REGISTER_SET(0xBBBBAAAA);
        // Hang the device
    }
}