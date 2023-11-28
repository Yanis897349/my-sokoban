/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** box
*/

#pragma once
#include "position.h"

typedef struct box_s {
    char c;
    position_t *pos;
} box_t;

box_t *create_box(char **map);
