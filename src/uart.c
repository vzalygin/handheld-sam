#include "uart.h"

int uart_putchar(char c, FILE * stream) {
   while(!(UCSR1A & 1 << UDRE1));
   if (c == '\n') {
      UDR1 = '\r';
   } else {
      UDR1 = c;
   }
   return 0;
}

int uart_getchar(FILE *stream) {
    while (!(UCSR1A & 1 << RXC1));
    return UDR1;
}

FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_stdin  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
