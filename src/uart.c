#include "uart.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include "buffer.h"

static volatile buffer_t INPUT_BUFFER NOINITMEM;

void init_uart() {
    UBRR1H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR1L = (uint8_t)(UBRR_VALUE);

    UCSR1A = 0;                              // U2X1 = 0 (обычный режим)
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);  // 8 бит, без чётности, 1 стоп
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) |
             (1 << RXCIE1);  // включить RX и TX, прерывание по чтению
    INPUT_BUFFER = make_buffer();
}

int putchar_uart(char c, FILE* stream) {
    while (!(UCSR1A & 1 << UDRE1));
    if (c == '\n') {
        putchar_uart('\r', NULL);
    }
    UDR1 = c;
    return 0;
}

int getchar_uart(FILE* stream) {
    // while (!(UCSR1A & 1 << RXC1));
    // return UDR1;
    return buffer_read(&INPUT_BUFFER);
}

ISR(USART1_RX_vect) {
    PORTB ^= (1 << PB0);
    buffer_write(&INPUT_BUFFER, UDR1);
}

FILE uart_stdout = FDEV_SETUP_STREAM(putchar_uart, NULL, _FDEV_SETUP_WRITE);
FILE uart_stdin = FDEV_SETUP_STREAM(NULL, getchar_uart, _FDEV_SETUP_READ);
