#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    memcpy(NULL, NULL, 0);

    int test_array[50] = {0};

    int *dynamic_test = malloc(sizeof(int));
    if(dynamic_test == NULL) {
        __asm("BKPT");
    }

    void *dynamic_test_ovf = malloc(0x1000);
    if(dynamic_test_ovf == NULL) {
        __asm("BKPT");
    }
//   free(dynamic_test_ovf);
//   void *dynamic_test_ovf2 = malloc(0x1000);

    // printf("Hello, World\n");
    while (1)
    {
        __asm("LDR  r0, = 0xAAAAAAAA");
        __asm("NOP");
    }

}

