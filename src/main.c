#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <avr/delay.h>

#include "help.h"
#include "player.h"
#include "sam.h"
#include "translator.h"
#include "uart.h"
#include "xmem.h"

#define INPUT_SIZE 255

static volatile char player_input[INPUT_SIZE] NOINITMEM;

// void init_led() { DDRB |= (1 << PB0); }
// void led_on() { PORTB &= ~(1 << PB0); }
// void led_off() { PORTB |= (1 << PB0); }

void init() {
    // xmem должен стоять первым
    init_xmem();
    // init_led();
    init_uart();
    init_player();
}

void player_callback(volatile player_data_t* data) {
    free(data->buffer);
    printf("%s\n", player_input);
}

void say(char* input, int phonetic) {
    char translated[INPUT_SIZE] = "\0";
    char current_word[INPUT_SIZE] = "\0";
    strcpy(current_word, input);
    strncat(input, " ", INPUT_SIZE);

    if (debug) printf("input: %s\n", input);
    for (int i = 0; input[i] != 0; i++) input[i] = toupper((int)input[i]);
    translate(translated, input, INPUT_SIZE);
    input = translated;
    if (debug) printf("translated: %s\n", input);

    if (debug) {
        if (phonetic) {
            printf("phonetic input: %s\n", input);
        } else {
            printf("text input: %s\n", input);
        }
    }

    if (!phonetic) {
        strncat(input, "[", INPUT_SIZE);
        if (!TextToPhonemes((unsigned char*)input)) {
            return;
        }
        if (debug) {
            printf("phonetic input: %s\n", input);
        }
    } else {
        strncat(input, "\x9b", INPUT_SIZE);
    }

    // led_on();
    SetInput(input);
    if (!SAMMain()) {
        print_usage();
    }
    // led_off();

    if (debug) printf("length: %d\n", GetBufferLength() / 50);

    wait_player();
    strcpy(player_input, current_word);
    play(make_player_data(GetBuffer(), GetBufferLength() / 50),
         player_callback);
}

void loop() {
    unsigned char number;
    int phonetic = 0;
    char input[INPUT_SIZE];
    int i;
    for (i = 0; i < INPUT_SIZE; ++i) input[i] = 0;
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
                printf("-debug enabled\n");
            } else {
                debug = 0;
                printf("-debug disabled\n");
            }
        } else if (strcmp(input, "-pitch") == 0) {
            scanf("%hhu", &number);
            SetPitch(number);
            printf("-pitch %hhu\n", number);
        } else if (strcmp(input, "-speed") == 0) {
            scanf("%hhu", &number);
            SetSpeed(number);
            printf("-speed %hhu\n", number);
        } else if (strcmp(input, "-mouth") == 0) {
            scanf("%hhu", &number);
            SetMouth(number);
            printf("-mouth %hhu\n", number);
        } else if (strcmp(input, "-throat") == 0) {
            scanf("%hhu", &number);
            SetThroat(number);
            printf("-throat %hhu\n", number);
        } else if (strcmp(input, "-sing") == 0) {
            if (!singmode) {
                singmode = 1;
                printf("-sing enabled\n");
            } else {
                singmode = 0;
                printf("-sing disabled\n");
            }
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
}
