#include <avr/interrupt.h>
#include <avr/io.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "help.h"
#include "sam.h"
#include "uart.h"

#define BAUD 9600UL
#define UBRR1_VALUE ((F_CPU / (16UL * BAUD)) - 1)

FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_stdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

extern int debug;

static char* speaker_buffer;
static unsigned int speaker_buffer_length;
static unsigned int speaker_buffer_index;

ISR(TIMER1_COMPA_vect) {
    OCR0 = speaker_buffer[speaker_buffer_index++];  // Отправляем в PWM регистр
                                                    // (8-бит)
    PORTD ^= (1 << PD0);

    if (speaker_buffer_index >= speaker_buffer_length) {
        TIMSK = (0 << OCIE1A);  // disable int
        PORTD |= (1 << PD0);
        printf("said\n");
    }
    sei();
}

void init_xmem() {
    // XMCRA = (1 << SRW11) | (1 << SRW10) | (1 << SRW01) | (1 << SRW00);
    XMCRA = 0;
    XMCRB = 0;
    MCUCR = (1 << SRE);
}

void init_uart() {
    UBRR1H = (uint8_t)(UBRR1_VALUE >> 8);
    UBRR1L = (uint8_t)(UBRR1_VALUE);

    UCSR1A = 0;                              // U2X1 = 0 (обычный режим)
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);  // 8 бит, без чётности, 1 стоп
    UCSR1B = (1 << RXEN1) | (1 << TXEN1);    // включить RX и TX
}

void init_io() { DDRB |= (1 << PD0); }

void init_pwm() {        // timer 0
    DDRB |= (1 << PB4);  // OC0 (PWM)
    // Fast PWM, non-inverting, prescaler = 1
    OCR0 = 0;
    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00);
}

void init_timer(void) {                   // timer 1
    TCCR1B = (1 << WGM12) | (1 << CS10);  // CTC mode, prescaler=1
    OCR1A = 361;             // (F_CPU / SAMPLE_RATE) - 1;   // timer period
    TIMSK |= (0 << OCIE1A);  // disable int
}

void say(char* input, int phonetic) {
    strncat(input, " ", 255);
    printf("input: %s\n", input);
    int i;
    for (i = 0; input[i] != 0; i++) input[i] = toupper((int)input[i]);
    if (debug) {
        if (phonetic) {
            printf("phonetic input: %s\n", input);
        } else {
            printf("text input: %s\n", input);
        }
    }

    if (!phonetic) {
        strncat(input, "[", 255);
        if (!TextToPhonemes((unsigned char*)input)) {
            return;
        }
        if (debug) {
            printf("phonetic input: %s\n", input);
        }
    } else {
        strncat(input, "\x9b", 255);
    }

    SetInput(input);
    if (!SAMMain()) {
        print_usage();
    }

    speaker_buffer = GetBuffer();
    speaker_buffer_length = GetBufferLength() / 50;
    free(speaker_buffer);
    // // speaker_buffer_length = speaker_buffer_length / 50;
    // speaker_buffer_index = 0;
    // PORTD = (0 << PD0);
    // TIMSK |= (1 << OCIE1A);  // enable int
}

int main() {
    stdin = &uart_stdin;
    stdout = &uart_stdout;

    init_xmem();
    init_uart();
    init_io();
    init_pwm();
    init_timer();

    unsigned char number;
    int phonetic = 0;
    char input[256];
    int i;
    for (i = 0; i <= 255; ++i) input[i] = 0;
    debug = 0;

    printf("READY\n> ");

    // for (;;) {
    //     uint8_t b;
    //     scanf("%c", &b);
    //     PORTB ^= (1 << PD0);
    //     printf("%c", b);
    // }

    // strncpy(input, "hello", 255);
    // say(input, phonetic);
    while (1) {
        scanf("%255s", input);
        if (input[0] != '-') {
            say(input, phonetic);
        } else if (strcmp(input, "-help") == 0) {
            print_usage();
        } else if (strcmp(input, "-debug") == 0) {
            if (!debug) {
                debug = 1;
                printf("debug enabled\n");
            } else {
                debug = 0;
                printf("debug disabled\n");
            }
        } else if (strcmp(input, "-pitch") == 0) {
            scanf("%hhu", &number);
            SetPitch(number);
            printf("set pitch %hhu\n", number);
        } else if (strcmp(input, "-speed") == 0) {
            scanf("%hhu", &number);
            SetSpeed(number);
            printf("set speed %hhu\n", number);
        } else {
            printf("unknown command %s\n", input);
        }
        printf("> ");
    }

    return 0;
}
