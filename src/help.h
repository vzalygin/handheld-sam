#ifndef HELP_H
#define HELP_H

#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#define strcpy_P strcpy
#define HELP_SIZE 37
static const char HELP_MSG[HELP_SIZE][60] PROGMEM = {
   "options:\n",
   "    -phonetic        enters phonetic mode. (see below)    \n",
   "    -pitch number    set pitch value       (default=64)   \n",
   "    -speed number    set speed value       (default=72)   \n",
   "    -throat number   set throat value      (default=128)  \n",
   "    -mouth number    set mouth value       (default=128)  \n",
   "    -sing            special treatment of pitch           \n",
   "    -debug           print additional debug messages    \n\n",
   "     VOWELS                            VOICED CONSONANTS  \n",
   "IY           f(ee)t                    R        red       \n",
   "IH           p(i)n                     L        allow     \n",
   "EH           beg                       W        away      \n",
   "AE           Sam                       W        whale     \n",
   "AA           pot                       Y        you       \n",
   "AH           b(u)dget                  M        Sam       \n",
   "AO           t(al)k                    N        man       \n",
   "OH           cone                      NX       so(ng)    \n",
   "UH           book                      B        bad       \n",
   "UX           l(oo)t                    D        dog       \n",
   "ER           bird                      G        again     \n",
   "AX           gall(o)n                  J        judge     \n",
   "IX           dig(i)t                   Z        zoo       \n",
   "                       ZH       plea(s)ure                \n",
   "   DIPHTHONGS                          V        seven     \n",
   "EY           m(a)de                    DH       (th)en    \n",
   "AY           h(igh)                                       \n",
   "OY           boy                                          \n",
   "AW           h(ow)                     UNVOICED CONSONANTS\n",
   "OW           slow                      S         Sam      \n",
   "UW           crew                      Sh        fish     \n",
   "                                       F         fish     \n",
   "                                       TH        thin     \n",
   " SPECIAL PHONEMES                      P         poke     \n",
   "UL           sett(le) (=AXL)           T         talk     \n",
   "UM           astron(omy) (=AXM)        K         cake     \n",
   "UN           functi(on) (=AXN)         CH        speech   \n",
   "Q            kitt-en (glottal stop)    /H        a(h)ead  \n"
};
static char help_buffer[100];

static void print_usage() {
   uint8_t i;
   for (i = 0; i < HELP_SIZE; ++i) {
      strcpy_P(help_buffer, HELP_MSG[i]);
      printf("%s", help_buffer);
   }
}

#endif
