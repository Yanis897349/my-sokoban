/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** game
*/

#include "my_sokoban.h"
#include "player.h"
#include "box.h"
#include "storage.h"
#include "include/my_strings.h"
#include <stdlib.h>

static int my_array_len(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}

static char **my_strcpy_array(char **map)
{
    char **new_map = malloc(sizeof(char *) * (my_array_len(map) + 1));

    if (new_map == NULL)
        return NULL;
    for (int i = 0; map[i] != NULL; i++) {
        new_map[i] = my_strdup(map[i]);
        if (new_map[i] == NULL)
            return NULL;
    }
    new_map[my_array_len(map)] = NULL;
    return new_map;
}

void reset_game(game_t *game)
{
    for (int i = 0; game->map[i] != NULL; i++) {
        for (int j = 0; game->map[i][j] != '\0'; j++) {
            game->map[i][j] = game->copy->map[i][j];
        }
    }
    game->player->pos->x = game->copy->player->pos->x;
    game->player->pos->y = game->copy->player->pos->y;
    game->player->c = game->copy->player->c;
    for (int i = 0; game->boxes[i] != NULL; i++) {
        game->boxes[i]->pos->x = game->copy->boxes[i]->pos->x;
        game->boxes[i]->pos->y = game->copy->boxes[i]->pos->y;
        game->boxes[i]->c = game->copy->boxes[i]->c;
    }
    game->state = PLAYING;
}

game_t *make_game_copy(game_t *game)
{
    game_t *game_cpy = malloc(sizeof(game_t));

    if (game_cpy == NULL)
        return NULL;
    game_cpy->map = my_strcpy_array(game->map);
    game_cpy->player = create_player(game_cpy->map);
    game_cpy->nb_boxes = game->nb_boxes;
    game_cpy->nb_storages = game->nb_storages;
    game_cpy->boxes = create_boxes(game_cpy->map, game->nb_boxes);
    game_cpy->storages = create_storages(game_cpy->map, game->nb_storages);
    game_cpy->state = game->state;
    return game_cpy;
}
