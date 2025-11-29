#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "help.h"
#include "player.h"
#include "sam.h"
#include "uart.h"
#include "xmem.h"

extern int debug;

void init_led() { DDRB |= (1 << PB0); }
void led_on() { PORTB &= ~(1 << PB0); }
void led_off() { PORTB |= (1 << PB0); }

void init() {
    init_xmem();
    init_led();
    init_uart();
    init_player();
}

void player_callback(volatile player_data* data) {
    if (debug) printf("said\n");
    free(data->buffer);
}

void say(char* input, int phonetic) {
    strncat(input, " ", 255);
    if (debug) printf("input: %s\n", input);
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

    led_on();
    SetInput(input);
    if (!SAMMain()) {
        print_usage();
    }
    led_off();

    if (debug) printf("length: %d\n", GetBufferLength() / 50);

    wait_player();
    play(make_player_data(GetBuffer(), GetBufferLength() / 50),
         player_callback);
}

void loop() {
    unsigned char number;
    int phonetic = 0;
    char input[256];
    int i;
    for (i = 0; i <= 255; ++i) input[i] = 0;
    debug = 0;

    printf("READY\n> ");

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
    }
}

int main() {
    stdin = &uart_stdin;
    stdout = &uart_stdout;

    init();
    sei();

    loop();

    while (1);

    return 0;
}
