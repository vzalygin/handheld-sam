#ifndef XMEM_H
#define XMEM_H

#include <avr/interrupt.h>
#include <avr/io.h>

static void init_xmem() {
    // XMCRA = (1 << SRW11) | (1 << SRW10) | (1 << SRW01) | (1 << SRW00);
    XMCRA = 0;
    XMCRB = 0;
    MCUCR = (1 << SRE);
}

#endif
