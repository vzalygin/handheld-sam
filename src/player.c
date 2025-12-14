#include "player.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

static volatile player_data_t data;
static volatile unsigned int pos;
static volatile callback_func_t callback;
static volatile int blocked;

void stop_pwm0() { 
    DDRB &= ~(1 << PB4);
    TCCR0 = 0;
    OCR0 = 0; 
}

void start_pwm0() {
    DDRB |= (1 << PB4);
    // Fast PWM, non-inverting, prescaler = 1
    // Частота ШИМ = 8 МГц / (1 * 256) ~ 31.25 кГц
    TCCR0 = (1 << WGM00) | (1 << WGM01) |  // Fast PWM
            (1 << COM01) |                 // non-inverting
            (1 << CS00);                   // прескейлер /1
    OCR0 = 0;
}

// прескейлер /1
void start_timer1() { TCCR1B |= (1 << CS10); }

void stop_timer1() { TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); }

void init_timer1() {
    TCCR1A = 0;             // CTC по OCR1A
    TCCR1B = (1 << WGM12);  // CTC mode
    OCR1A = 362;            // 8 МГц и 22050 Гц при прескейлер /1

    // Прерывание по совпадению с OCR1A
    TIMSK |= (1 << OCIE1A);

    stop_timer1();
}

ISR(TIMER1_COMPA_vect) {
    if (pos == data.size) {
        stop_pwm0();
        stop_timer1();
        blocked = 0;
        if (callback != NULL) callback(&data);
        return;
    }

    OCR0 = data.buffer[pos++];
}

void init_player() {
    pos = 0;
    callback = NULL;
    init_timer1();
}

player_data_t make_player_data(char* buffer, unsigned int size) {
    player_data_t data;
    data.buffer = buffer;
    data.size = size;
    return data;
}

void play(player_data_t _data, callback_func_t _callback) {
    blocked = 1;
    data = _data;
    callback = _callback;
    pos = 0;
    start_pwm0();
    start_timer1();
}

int is_player_blocked() { return blocked; }

void wait_player() { while (is_player_blocked()); }
