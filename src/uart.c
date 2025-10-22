#include "uart.h"

int uart_putchar(char c, FILE * stream) {
   while(!(UCSR0A & 1 << UDRE));
   if (c == '\n') {
      UDR0 = '\r';
   } else {
      UDR0 = c;
   }
   return 0;
}

int uart_getchar(FILE *stream) {
    while (!(UCSR0A & 1 << RXC0));
    return UDR0;
}

FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_stdin  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
