/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** player
*/

#include "player.h"
#include "my_sokoban.h"
#include <stdlib.h>

static position_t *get_player_position(char **map)
{
    position_t *player_position = malloc(sizeof(position_t));
    int pos_in_buffer = - 1;

    if (player_position == NULL)
        return NULL;
    for (int i = 0; map[i] != NULL; i++) {
        pos_in_buffer = get_pos_in_buffer(map[i], 'P');
        if (pos_in_buffer != -1) {
            player_position->x = pos_in_buffer;
            player_position->y = i;
            return player_position;
        }
    }
    return NULL;
}

player_t *create_player(char **map)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        return NULL;
    player->c = 'P';
    player->pos = get_player_position(map);
    if (player->pos == NULL)
        return NULL;
    return player;
}
