#ifndef UART_H
#define UART_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

#include "memmanagment.h"

#define BAUD_RATE 9600UL
#define UBRR1_VALUE ((F_CPU / (16UL * BAUD_RATE)) - 1)

extern FILE uart_stdout;
extern FILE uart_stdin;

void init_uart();

int putchar_uart(char c, FILE* stream);
int getchar_uart(FILE* stream);

#endif
