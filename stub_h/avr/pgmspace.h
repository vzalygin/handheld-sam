#ifndef PGMSPACE_H
#define PGMSPACE_H

#define PROGMEM /*PROGMEM*/

static const char pgm_read_byte(const char * ptr) {
    return *ptr;
}

#endif
