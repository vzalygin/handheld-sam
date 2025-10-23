#ifndef RENDERTABS_H
#define RENDERTABS_H

#include <avr/pgmspace.h>

#include "memmanagment.h"

extern const unsigned char tab48426[5] PROGMEM;

extern const unsigned char tab47492[] PROGMEM;

extern const unsigned char amplitudeRescale[] PROGMEM;

extern const unsigned char blendRank[] PROGMEM;

extern const unsigned char outBlendLength[] PROGMEM;

extern const unsigned char inBlendLength[] PROGMEM;

extern unsigned char sampledConsonantFlags[] DATAMEM;

extern unsigned char freq1data[] DATAMEM;

extern unsigned char freq2data[] DATAMEM;

extern unsigned char freq3data[] PROGMEM;

extern const unsigned char ampl1data[] PROGMEM;

extern const unsigned char ampl2data[] PROGMEM;

extern const unsigned char ampl3data[] PROGMEM;

extern const signed char sinus[256] PROGMEM;

extern const unsigned char rectangle[] PROGMEM;

extern const unsigned char sampleTable[0x500] PROGMEM;

#endif
