/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** box
*/

#include "box.h"
#include <stdlib.h>

static position_t *get_box_position(char **map)
{
    position_t *box_position = malloc(sizeof(position_t));
    int pos_in_buffer = - 1;

    if (box_position == NULL)
        return NULL;
    for (int i = 0; map[i] != NULL; i++) {
        pos_in_buffer = get_pos_in_buffer(map[i], 'X');
        if (pos_in_buffer != -1) {
            box_position->x = pos_in_buffer;
            box_position->y = i;
            return box_position;
        }
    }
    return NULL;
}

box_t *create_box(char **map)
{
    box_t *box = malloc(sizeof(box_t));

    if (box == NULL)
        return NULL;
    box->c = 'X';
    box->pos = get_box_position(map);
    if (box->pos == NULL)
        return NULL;
    return box;
}
