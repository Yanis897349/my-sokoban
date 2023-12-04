/*
** EPITECH PROJECT, 2023
** my-sokoban
** File description:
** my_sokoban
*/

#pragma once
#define WALL_CHAR '#'
#define PLAYER_CHAR 'P'
#define DEFAULT_CHAR ' '
#define BOX_CHAR 'X'
#define STORAGE_CHAR 'O'

typedef struct player_s player_t;
typedef struct box_s box_t;
typedef struct storage_s storage_t;

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
