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

void move_box(int key, player_t *player, char **map)
{
    position_t *new_pos = malloc(sizeof(position_t));
    position_t *box_pos = malloc(sizeof(position_t));

    if (new_pos == NULL || box_pos == NULL)
        return;
    box_pos->x = player->pos->x;
    box_pos->y = player->pos->y;
    new_pos = calculate_new_position(key, box_pos, new_pos);
    box_pos->x = new_pos->x;
    box_pos->y = new_pos->y;
    new_pos = calculate_new_position(key, box_pos, new_pos);
    if (is_box_moveable(map, new_pos->x, new_pos->y) == 1) {
        map[box_pos->y][box_pos->x] = ' ';
        map[new_pos->y][new_pos->x] = 'X';
        player->pos->x = box_pos->x;
        player->pos->y = box_pos->y;
    }
    free(new_pos);
    free(box_pos);
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
