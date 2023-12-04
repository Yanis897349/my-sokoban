/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** position
*/

#pragma once

typedef struct position_s {
    int x;
    int y;
} position_t;

int get_pos_count(char **map, char c);
position_t *get_position(char **map, char c);
position_t **get_positions(char **map, char c, int count);
position_t *calculate_new_position(int key, position_t *current_pos,
    position_t *new_pos);
