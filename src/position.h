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

int get_pos_in_buffer(char *buffer, char c);
