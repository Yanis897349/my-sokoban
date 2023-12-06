/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** player
*/

#include "player.h"
#include "box.h"
#include "my_sokoban.h"
#include "position.h"
#include <curses.h>
#include <stdlib.h>
#include <ncurses.h>

static int is_player_moveable(char **map, int new_x, int new_y)
{
    if (map[new_y][new_x] != WALL_CHAR && map[new_y][new_x] != '\0'
        && map[new_y][new_x] != BOX_CHAR)
        return MOVE;
    if (map[new_y][new_x] == BOX_CHAR)
        return PUSH;
    return NONE;
}

static void player_move(game_t *game, position_t *new_pos)
{
    char **map = game->map;
    player_t *player = game->player;

    map[player->pos->y][player->pos->x] = player->c;
    player->c = map[new_pos->y][new_pos->x];
    player->pos->x = new_pos->x;
    player->pos->y = new_pos->y;
    map[new_pos->y][new_pos->x] = PLAYER_CHAR;
}

void player_make_action(int key, game_t *game, char **map)
{
    position_t *new_pos = malloc(sizeof(position_t));
    box_t *box = NULL;
    int move_type = 0;

    if (new_pos == NULL)
        return;
    calculate_new_position(key, game->player->pos, new_pos);
    move_type = is_player_moveable(map, new_pos->x, new_pos->y);
    switch (move_type) {
    case MOVE:
        player_move(game, new_pos);
        break;
    case PUSH:
        box = get_box_at_pos(game->boxes, new_pos->x, new_pos->y);
        move_box(key, game, box);
        break;
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
