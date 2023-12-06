/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** storage
*/

#include "storage.h"
#include "position.h"
#include "my_sokoban.h"
#include <stdlib.h>

int get_storage_count(char **map)
{
    int storage_count = 0;

    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\0'; j++)
            storage_count = (map[i][j] == STORAGE_CHAR) ? storage_count + 1
                : storage_count;
    return storage_count;
}

static storage_t *create_storage(position_t *pos)
{
    storage_t *storage = malloc(sizeof(storage_t));

    if (storage == NULL)
        return NULL;
    storage->c = STORAGE_CHAR;
    storage->pos = pos;
    if (storage->pos == NULL)
        return NULL;
    return storage;
}

storage_t **create_storages(char **map, int storage_count)
{
    storage_t **storages = malloc(sizeof(storage_t *) * (storage_count + 1));
    position_t **positions = get_positions(map, STORAGE_CHAR, storage_count);

    if (storages == NULL)
        return NULL;
    if (positions == NULL)
        return NULL;
    for (int i = 0; i < storage_count; i++) {
        storages[i] = create_storage(positions[i]);
        if (storages[i] == NULL)
            return NULL;
    }
    storages[storage_count] = NULL;
    return storages;
}
