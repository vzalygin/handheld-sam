#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_SIZE 256

typedef struct buffer_t {
    char* buf;
    int begin;
    int end;
} buffer_t;

buffer_t make_buffer();

int buffer_is_empty(volatile buffer_t* buffer);

void buffer_write(volatile buffer_t* buffer, char ch);

char buffer_read(volatile buffer_t* buffer);

#endif
