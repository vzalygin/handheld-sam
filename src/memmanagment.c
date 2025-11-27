#include "memmanagment.h"

char PRINTF_FMT_BUFFER[256] NOINITMEM;

const char* copy_pgm_str(const char* pgm_str) {
    strcpy_P(PRINTF_FMT_BUFFER, pgm_str);
    return PRINTF_FMT_BUFFER;
}
