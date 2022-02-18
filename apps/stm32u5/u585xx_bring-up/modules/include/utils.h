#ifndef MODULES_UTILS_H
#define MODULES_UTILS_H

#define ExitOnError(x)  \
    do {                \
        if (0 != (x)) { \
            goto exit;  \
        }               \
    } while (0);

#define Assert(_expression, _expected)      \
    do {                                    \
        if ((_expression) != (_expected)) { \
            while (1)                       \
                ;                           \
        }                                   \
    } while (0);

#endif
