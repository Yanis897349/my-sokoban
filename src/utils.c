/*
** EPITECH PROJECT, 2023
** my-sokoban
** File description:
** utils
*/

#include "include/my_strings.h"
#include "include/my_std.h"
#include "my_sokoban.h"
#include "player.h"
#include "box.h"
#include "storage.h"
#include <stdlib.h>

static void free_storages(storage_t **storages)
{
    for (int i = 0; storages[i] != NULL; i++) {
        free(storages[i]->pos);
        free(storages[i]);
    }
    free(storages);
}

static void free_boxes(box_t **boxes)
{
    for (int i = 0; boxes[i] != NULL; i++) {
        free(boxes[i]->pos);
        free(boxes[i]);
    }
    free(boxes);
}

static void free_player(player_t *player)
{
    free(player->pos);
    free(player);
}

void free_game(game_t *game)
{
    free_player(game->player);
    free_boxes(game->boxes);
    free_storages(game->storages);
    my_freearray(game->map);
    free(game);
}

char **get_map(char *filepath)
{
    char *buffer = NULL;
    char **map = NULL;

    buffer = file_to_buffer(filepath);
    if (buffer == NULL)
        return NULL;
    map = buffer_to_array(buffer, '\n');
    free(buffer);
    if (map == NULL)
        return NULL;
    return map;
}
