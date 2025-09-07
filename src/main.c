#include <avr/io.h>

#include <stdio.h>
#include <stdlib.h>

#include "sam.h"

void XMEM_init(void)
{
    // External memory interface enable
    MCUCR |= (1<SRE);
    XMCRA = 0;
    //PC7..PC5 released pins
    XMCRB |= (1<XMM1)|(1<XMM0);
}

int main() {
    while(1);
}
