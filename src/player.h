/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** player
*/

#pragma once
#include "position.h"

typedef struct player_s {
    char c;
    position_t *pos;
} player_t;

player_t *create_player(char **map);
