#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include <stdio.h>
#include <inttypes.h>

#include "memmanagment.h"

extern FILE uart_stdout;
extern FILE uart_stdin;

#endif
