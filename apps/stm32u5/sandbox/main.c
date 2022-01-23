#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbg_utils.h"

int main() {
  LL_CANARY_REGISTER_SET(0x0002000);
//   memcpy(NULL, NULL, 0);
  LL_CANARY_REGISTER_SET(0x0002001);

  int test_array[50] = {0};
  LL_CANARY_REGISTER_SET(0x0002002);

//   int *dynamic_test = malloc(sizeof(int));
//   if(dynamic_test == NULL) {
//       LL_CANARY_REGISTER_SET(0x00020010);
//       __asm("BKPT");
//   }

//   void *dynamic_test_ovf = malloc(0x1000);
//   if(dynamic_test_ovf == NULL) {
//       LL_CANARY_REGISTER_SET(0x00020010);
//       __asm("BKPT");
//   }
//   LL_CANARY_REGISTER_SET(0x0002003);
//   free(dynamic_test_ovf);
//   void *dynamic_test_ovf2 = malloc(0x1000);

  printf("Hello, World\n");
  LL_CANARY_REGISTER_SET(0x0002004);

  while (1) {
    LL_CANARY_REGISTER_SET(0x0002005);
  }
  LL_CANARY_REGISTER_SET(0x0002006);
}