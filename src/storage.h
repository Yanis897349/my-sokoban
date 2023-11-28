/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** storage
*/

#pragma once
#include "position.h"

typedef struct storage_s {
    char c;
    position_t *pos;
} storage_t;

storage_t *create_storage(char **map);
