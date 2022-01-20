#include "stddef.h"

typedef void (*isr_handler)(void);

void handler_reset(void);
int main(int argc, char** argv);


isr_handler init_vec[] __attribute__((section(".init_vec"))) = {
    (isr_handler)0x20005000, handler_reset};

void handler_reset(void) { main(0, NULL); }

int main(int argc, char** argv) { return 1; }