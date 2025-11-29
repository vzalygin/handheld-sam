#include "uart.h"

void init_uart() {
    UBRR1H = (uint8_t)(UBRR1_VALUE >> 8);
    UBRR1L = (uint8_t)(UBRR1_VALUE);

    UCSR1A = 0;                              // U2X1 = 0 (обычный режим)
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);  // 8 бит, без чётности, 1 стоп
    UCSR1B = (1 << RXEN1) | (1 << TXEN1);    // включить RX и TX
}

int uart_putchar(char c, FILE* stream) {
    while (!(UCSR1A & 1 << UDRE1));
    if (c == '\n') {
        uart_putchar('\r', NULL);
    }
    UDR1 = c;
    return 0;
}

int uart_getchar(FILE* stream) {
    while (!(UCSR1A & 1 << RXC1));
    return UDR1;
}

FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_stdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
