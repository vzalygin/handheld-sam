#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "SamTabs.h"
#include "memmanagment.h"

extern int debug DATAMEM;

void PrintPhonemes(unsigned char *phonemeindex, unsigned char *phonemeLength,
                   unsigned char *stress);
void PrintOutput(unsigned char *flag, unsigned char *f1, unsigned char *f2,
                 unsigned char *f3, unsigned char *a1, unsigned char *a2,
                 unsigned char *a3, unsigned char *p);

void PrintRule(int offset);

#endif
