#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

char *__env[1] = {0};
char **environ = __env;

int _kill(int pid, int sig) {
  errno = EINVAL;
  return -1;
}

void _exit(int status) {
  _kill(status, -1);
  while (1) {
    // Hang the device
  }
}

caddr_t _sbrk(int incr) {
  extern char *_ebss;
  extern char *_eheap;
  static char *heap_end;
  char *prev_heap_end;

  if (heap_end == 0) {
    heap_end = &_ebss;
  }

  prev_heap_end = heap_end;
  if (heap_end + incr > &_eheap) {
    errno = ENOMEM;
    return (caddr_t)-1;
  }

  heap_end += incr;

  return (caddr_t)prev_heap_end;
}

int _write(int file, char *ptr, int len) {
  for (int data_idx = 0; data_idx < len; data_idx++) {
    __io_putchar(*ptr++);
  }

  return len;
}

int _read(int file, char *ptr, int len) {
  for (int data_idx = 0; data_idx < len; data_idx++) {
    *ptr++ = __io_getchar();
  }

  return len;
}

int _close(int file) { return -1; }

int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _lseek(int file, int ptr, int dir) { return 0; }

int _isatty(int file) { return 1; }