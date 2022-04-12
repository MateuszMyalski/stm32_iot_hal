#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "serial_stdio.h"
#include "stm32u585xx.h"
#include "utils.h"

#ifndef EOF
#define EOF (-1)
#endif // EOF

extern int errno;

static USART_TypeDef *stdio_usart_instance = NULL;


void serial_stdio_init(USART_TypeDef * instance) {
    stdio_usart_instance = instance;
}

int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

void _exit(int status) {
    _kill(status, -1);
    while (1) {
        __asm("NOP");
        // Hang the device
    }
}

caddr_t _sbrk(int incr) {
    extern char *_end;
    extern char *_eheap;
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_end;
    }

    prev_heap_end = heap_end;
    if (heap_end + incr > &_eheap) {
        errno = ENOMEM;
        __asm("BKPT");
        return (caddr_t)-1;
    }

    heap_end += incr;

    return (caddr_t)prev_heap_end;
}

int putchar(signed int c) {
#ifdef USE_ITM_WRITE
    ITM_SendChar(c);
#else
    hal_usart_putchar(stdio_usart_instance, (char)c);
#endif  // USE_ITM_WRITE

    return c;
}

#ifdef USE_TINY_PRINTF
void _putchar(char character) {
    putchar(character);
}
#endif  // USE_TINY_PRINTF

int _write(int file, char *ptr, int len) {

    Assert(NULL == stdio_usart_instance);

    for (int data_idx = 0; data_idx < len; data_idx++) {
        putchar(*ptr++);
    }

    return len;
}

int _read(int file, char *ptr, int len) {
    for (int data_idx = 0; data_idx < len; data_idx++) {
#ifdef USE_ITM_READ
        *ptr++ = ITM_ReceiveChar();
#endif  // USE_ITM_READ
    }

    return len;
}

int _close(int file) {
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _isatty(int file) {
    return 1;
}