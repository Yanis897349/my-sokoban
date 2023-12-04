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

int is_box_stuck(char **map, box_t *box, player_t *player);
void move_box(int key, game_t *game, box_t *box);
box_t *get_box_at_pos(box_t **boxes, int x, int y);
box_t **create_boxes(char **map, int box_count);
