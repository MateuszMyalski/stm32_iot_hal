#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    while (1) {
        __asm("LDR  r0, = 0xAAAAAAAA");
        __asm("NOP");
    }
}
