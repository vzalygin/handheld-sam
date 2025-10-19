#ifndef PGMSPACE_H
#define PGMSPACE_H

#define PROGMEM /*PROGMEM*/

const unsigned char pgm_read_byte(const unsigned char * ptr) {
    return *ptr;
}

#endif
