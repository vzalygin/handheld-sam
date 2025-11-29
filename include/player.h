#ifndef PLAYER_H
#define PLAYER_H

typedef struct player_data {
    char* buffer;
    unsigned int size;
} player_data;

typedef void (*callback_func)(volatile player_data* data);

void init_player();

player_data make_player_data(char* buffer, unsigned int size);

void play(player_data data, callback_func callback);

int is_player_blocked();

void wait_player();

#endif
