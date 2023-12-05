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

static int is_char_valid(char c)
{
    if (c == ' ' || c == '\n' || c == WALL_CHAR || c == BOX_CHAR
        || c == STORAGE_CHAR || c == PLAYER_CHAR)
        return 1;
    return 0;
}

static int is_buffer_valid(char *buffer)
{
    int nb_player = 0;
    int nb_boxes = 0;
    int nb_storages = 0;
    int invalid_char = 0;

    for (int i = 0; buffer[i] != '\0'; i++) {
        nb_player += (buffer[i] == PLAYER_CHAR) ? 1 : 0;
        nb_boxes += (buffer[i] == BOX_CHAR) ? 1 : 0;
        nb_storages += (buffer[i] == STORAGE_CHAR) ? 1 : 0;
        invalid_char += (is_char_valid(buffer[i]) == 0) ? 1 : 0;
    }
    if (nb_player != 1 || nb_boxes != nb_storages)
        return 0;
    if (invalid_char != 0)
        return 0;
    return 1;
}

char **get_map(char *filepath)
{
    char *buffer = NULL;
    char **map = NULL;

    buffer = file_to_buffer(filepath);
    if (buffer == NULL)
        return NULL;
    if (!is_buffer_valid(buffer)) {
        free(buffer);
        return NULL;
    }
    map = buffer_to_array(buffer, '\n');
    free(buffer);
    if (map == NULL)
        return NULL;
    return map;
}
