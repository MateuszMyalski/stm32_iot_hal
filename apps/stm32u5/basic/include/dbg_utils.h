#ifndef DBG_UTILS_H
#define DBG_UTILS_H

// Debug inline asm to track major steps through CPU regs while init
#define LL_CANARY_REGISTER_SET(x) \
  do {                            \
    __asm("LDR  r0, = " #x);      \
  } while (0);

#define LL_CANARY_REGISTER_OR(x) \
  do {                            \
    __asm("LDR  r1, = " #x);      \
  } while (0);

#endif
