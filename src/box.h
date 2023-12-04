/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** box
*/

#pragma once
#include "position.h"
#include "player.h"

typedef struct box_s {
    char c;
    position_t *pos;
} box_t;

void move_box(int key, player_t *player, char **map);
box_t **create_boxes(char **map, int box_count);
