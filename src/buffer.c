#include "buffer.h"

#include <stdlib.h>
#include <stdio.h>

buffer_t make_buffer() {
    buffer_t buffer;
    buffer.buf = (char*)malloc(BUFFER_SIZE);
    buffer.begin = 0;
    buffer.end = 0;
    return buffer;
}

int buffer_is_empty(volatile buffer_t* buffer) {
    return (buffer->end - buffer->begin + BUFFER_SIZE) % BUFFER_SIZE == 0;
}

void buffer_write(volatile buffer_t* buffer, char ch) {
    buffer->buf[buffer->end] = ch;
    buffer->end = (buffer->end + 1) % BUFFER_SIZE;
}

char buffer_read(volatile buffer_t* buffer) {
    char ch;
    // блокируемся, пока в буфер кто-нибудь не напишет
    while (buffer_is_empty(buffer));
    ch = buffer->buf[buffer->begin];
    buffer->begin = (buffer->begin + 1) % BUFFER_SIZE;
    return ch;
}
