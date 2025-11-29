#include "memmanagment.h"

char COPY_PGM_BUFFER[256] NOINITMEM;

const char* copy_pgm_str(const char* pgm_str) {
    strcpy_P(COPY_PGM_BUFFER, pgm_str);
    return COPY_PGM_BUFFER;
}
