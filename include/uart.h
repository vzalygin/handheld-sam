#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include <stdio.h>
#include <inttypes.h>

#include "memmanagment.h"

#define BAUD    9600UL
#define UBRR1_VALUE ((F_CPU / (16UL * BAUD)) - 1)

extern FILE uart_stdout;
extern FILE uart_stdin;

#endif
