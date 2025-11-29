#ifndef PLAYER_H
#define PLAYER_H

typedef struct player_data_t {
    char* buffer;
    unsigned int size;
} player_data_t;

typedef void (*callback_func_t)(volatile player_data_t* data);

void init_player();

player_data_t make_player_data(char* buffer, unsigned int size);

void play(player_data_t data, callback_func_t callback);

int is_player_blocked();

void wait_player();

#endif
