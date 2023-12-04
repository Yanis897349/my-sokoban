/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** player
*/

#include "player.h"
#include "my_sokoban.h"
#include "position.h"
#include <curses.h>
#include <stdlib.h>
#include <ncurses.h>

static int is_player_moveable(char **map, int new_x, int new_y)
{
    if (map[new_y][new_x] != WALL_CHAR && map[new_y][new_x] != '\0'
        && map[new_y][new_x] != BOX_CHAR)
        return 1;
    if (map[new_y][new_x] == BOX_CHAR)
        return 2;
    return 0;
}

void move_player(int key, player_t *player, char **map)
{
    position_t *new_pos = malloc(sizeof(position_t));
    int move_type = 0;

    if (new_pos == NULL)
        return;
    calculate_new_position(key, player->pos, new_pos);
    move_type = is_player_moveable(map, new_pos->x, new_pos->y);
    if (move_type == 0)
        return;
    if (move_type == 1) {
        map[player->pos->y][player->pos->x] = player->c;
        player->c = map[new_pos->y][new_pos->x];
        player->pos->x = new_pos->x;
        player->pos->y = new_pos->y;
    }
    if (move_type == 2) {
        move_box(key, player, map);
    }
    free(new_pos);
}

player_t *create_player(char **map)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        return NULL;
    player->c = ' ';
    player->pos = get_position(map, PLAYER_CHAR);
    if (player->pos == NULL)
        return NULL;
    return player;
}
