#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include <stdio.h>
#include <inttypes.h>

#include "memmanagment.h"

int uart_putchar(char c, FILE * stream);
int uart_getchar(FILE *stream);

void uart_print(char * str);

#endif
