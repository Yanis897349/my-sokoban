/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** player
*/

#include "player.h"
#include "my_sokoban.h"
#include <stdlib.h>
#include <ncurses.h>

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

static int is_player_moveable(char **map, int new_x, int new_y)
{
    if (map[new_y][new_x] != WALL_CHAR && map[new_y][new_x] != '\0')
        return 1;
    return 0;
}

static position_t *calculate_new_position(int key, position_t *current_pos,
    position_t *new_pos)
{
    new_pos->x = current_pos->x;
    new_pos->y = current_pos->y;
    switch (key) {
        case KEY_UP:
            new_pos->y--;
            break;
        case KEY_DOWN:
            new_pos->y++;
            break;
        case KEY_LEFT:
            new_pos->x--;
            break;
        case KEY_RIGHT:
            new_pos->x++;
            break;
    }
    return new_pos;
}

void move_player(int key, player_t *player, char **map)
{
    position_t *new_pos = malloc(sizeof(position_t));

    if (new_pos == NULL)
        return;
    calculate_new_position(key, player->pos, new_pos);
    if (is_player_moveable(map, new_pos->x, new_pos->y)) {
        map[player->pos->y][player->pos->x] = player->c;
        player->c = map[new_pos->y][new_pos->x];
        player->pos->x = new_pos->x;
        player->pos->y = new_pos->y;
    }
    free(new_pos);
}

player_t *create_player(char **map)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        return NULL;
    player->c = ' ';
    player->pos = get_player_position(map);
    if (player->pos == NULL)
        return NULL;
    return player;
}
