/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** position
*/

#include "position.h"
#include <ncurses.h>
#include <stdlib.h>

int get_pos_count(char **map, char c)
{
    int pos_count = 0;

    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j] != '\0'; j++)
            pos_count = (map[i][j] == c) ? pos_count + 1 : pos_count;
    return pos_count;
}

static int get_pos_in_buffer(char *buffer, char c, int start)
{
    int i = start;

    for (; buffer[i] != '\0'; i++)
        if (buffer[i] == c)
            return i;
    return -1;
}

position_t *get_position(char **map, char c)
{
    position_t *pos = malloc(sizeof(position_t));
    int pos_in_buffer = - 1;

    if (pos == NULL)
        return NULL;
    for (int i = 0; map[i] != NULL; i++) {
        pos_in_buffer = get_pos_in_buffer(map[i], c, 0);
        if (pos_in_buffer != -1) {
            pos->x = pos_in_buffer;
            pos->y = i;
            return pos;
        }
    }
    return NULL;
}

static position_t *create_position(int x, int y)
{
    position_t *pos = malloc(sizeof(position_t));

    if (pos == NULL)
        return NULL;
    pos->x = x;
    pos->y = y;
    return pos;
}

position_t **get_positions(char **map, char c, int count)
{
    position_t **positions = malloc(sizeof(position_t *) * (count + 1));
    int index = 0;
    int pos_in_buffer = 0;
    position_t *pos = NULL;

    if (positions == NULL)
        return NULL;
    for (int i = 0; map[i] != NULL; i++) {
        pos_in_buffer = get_pos_in_buffer(map[i], c, 0);
        while (pos_in_buffer != -1) {
            pos = create_position(pos_in_buffer, i);
            positions[index] = pos;
            index++;
            pos_in_buffer++;
            pos_in_buffer = get_pos_in_buffer(map[i], c, pos_in_buffer);
        }
    }
    positions[index] = NULL;
    return positions;
}

position_t *calculate_new_position(int key, position_t *current_pos,
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
