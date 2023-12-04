/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** box
*/

#include "box.h"
#include "player.h"
#include "position.h"
#include "my_sokoban.h"
#include <curses.h>
#include <stdlib.h>
#include <ncurses.h>

static int is_box_moveable(char **map, int new_x, int new_y)
{
    if (map[new_y][new_x] != WALL_CHAR && map[new_y][new_x] != '\0'
        && map[new_y][new_x] != BOX_CHAR)
        return 1;
    return 0;
}

static box_t *create_box(char **map, position_t *pos)
{
    box_t *box = malloc(sizeof(box_t));

    if (box == NULL)
        return NULL;
    box->c = ' ';
    box->pos = pos;
    if (box->pos == NULL)
        return NULL;
    return box;
}

box_t *get_box_at_pos(box_t **boxes, int x, int y)
{
    for (int i = 0; boxes[i] != NULL; i++) {
        if (boxes[i]->pos->x == x && boxes[i]->pos->y == y)
            return boxes[i];
    }
    return NULL;
}

void move_box(int key, game_t *game, box_t *box)
{
    position_t *new_pos = malloc(sizeof(position_t));
    player_t *player = game->player;
    char **map = game->map;
    int move_type = 0;

    if (new_pos == NULL)
        return;
    calculate_new_position(key, box->pos, new_pos);
    move_type = is_box_moveable(map, new_pos->x, new_pos->y);
    if (move_type == 0)
        return;
    if (move_type == 1) {
        map[box->pos->y][box->pos->x] = box->c;
        box->c = map[new_pos->y][new_pos->x];
        box->pos->x = new_pos->x;
        box->pos->y = new_pos->y;
        map[box->pos->y][box->pos->x] = BOX_CHAR;
        player_make_action(key, game, map);
    }
    free(new_pos);
}

box_t **create_boxes(char **map, int box_count)
{
    box_t **boxes = malloc(sizeof(box_t *) * (box_count + 1));
    position_t **positions = get_positions(map, BOX_CHAR, box_count);

    if (boxes == NULL)
        return NULL;
    if (positions == NULL)
        return NULL;
    for (int i = 0; i < box_count; i++) {
        boxes[i] = create_box(map, positions[i]);
        if (boxes[i] == NULL)
            return NULL;
    }
    boxes[box_count] = NULL;
    return boxes;
}
