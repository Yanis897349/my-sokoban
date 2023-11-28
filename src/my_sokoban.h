/*
** EPITECH PROJECT, 2023
** my-sokoban
** File description:
** my_sokoban
*/

#pragma once

#include "box.h"
#include "storage.h"
#include "player.h"

typedef enum game_state_e {
    WIN = 0,
    DEFEAT = 1,
    PLAYING = 2
} game_state_t;

typedef struct game_s {
    char **map;
    player_t *player;
    box_t **boxes;
    storage_t **storages;
    int nb_boxes;
    int nb_storages;
    game_state_t state;
} game_t;
