/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** storage
*/

#include "storage.h"
#include <stdlib.h>

static position_t *get_storage_position(char **map)
{
    position_t *storage_position = malloc(sizeof(position_t));
    int pos_in_buffer = - 1;

    if (storage_position == NULL)
        return NULL;
    for (int i = 0; map[i] != NULL; i++) {
        pos_in_buffer = get_pos_in_buffer(map[i], 'O');
        if (pos_in_buffer != -1) {
            storage_position->x = pos_in_buffer;
            storage_position->y = i;
            return storage_position;
        }
    }
    return NULL;
}

storage_t *create_storage(char **map)
{
    storage_t *storage = malloc(sizeof(storage_t));

    if (storage == NULL)
        return NULL;
    storage->c = 'X';
    storage->pos = get_storage_position(map);
    if (storage->pos == NULL)
        return NULL;
    return storage;
}
