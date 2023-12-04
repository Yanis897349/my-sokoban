/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** player
*/

#pragma once
#include "position.h"
#include "my_sokoban.h"

typedef struct player_s {
    char c;
    position_t *pos;
} player_t;

typedef enum player_move_type_e {
    MOVE = 0,
    PUSH,
    NONE
} player_move_type_t;

void player_make_action(int key, game_t *game, char **map);
player_t *create_player(char **map);
