#ifndef BSP_UTILS_H
#define BSP_UTILS_H

#define ExitOnError(x)  \
    do {                \
        if (0 != (x)) { \
            goto exit;  \
        }               \
    } while (0);

#define Assert(_expr) do{    \
 while(!(_expr)) {           \
     /* Hang me up to dry */ \
     }                       \
}while(0);

#endif
