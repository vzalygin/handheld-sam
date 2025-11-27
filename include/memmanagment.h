#ifndef MEMMANAGMENT_H
#define MEMMANAGMENT_H

#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>

#define DATAMEM __attribute__((section(".data")))
#define NOINITMEM __attribute__((section(".noinit")))

#define printf(...) _PRINTF_IMPL(__VA_ARGS__)(__VA_ARGS__)
#define _PRINTF_IMPL(...)                                                      \
    _GET_MACRO(__VA_ARGS__, _PRINTF_IMPL_1, _PRINTF_IMPL_1, _PRINTF_IMPL_1,    \
               _PRINTF_IMPL_1, _PRINTF_IMPL_1, _PRINTF_IMPL_1, _PRINTF_IMPL_1, \
               _PRINTF_IMPL_1, _PRINTF_IMPL_1, _PRINTF_IMPL_0)
#define _GET_MACRO(_fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME
#define _PRINTF_IMPL_0(fmt)                    \
    do {                                       \
        static const char MSG[] PROGMEM = fmt; \
        printf(copy_pgm_str(MSG));             \
    } while (0)
#define _PRINTF_IMPL_1(fmt, ...)                \
    do {                                        \
        static const char MSG[] PROGMEM = fmt;  \
        printf(copy_pgm_str(MSG), __VA_ARGS__); \
    } while (0)

extern char PRINTF_FMT_BUFFER[256] NOINITMEM;
const char* copy_pgm_str(const char* pgm_str);

#endif
