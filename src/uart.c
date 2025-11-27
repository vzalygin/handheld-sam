#include "uart.h"

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

void uart_print(char* str) {
    uint8_t l = strlen(str);
    for (int i = 0; i < l; i++) {
        uart_putchar(str[i], NULL);
    }
}
