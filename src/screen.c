/*
** EPITECH PROJECT, 2023
** my-sokoban
** File description:
** screen
*/

#include <ncurses.h>
#include "include/my_strings.h"

static int get_max_line_size(char **map)
{
    int max = 0;

    for (int i = 0; map[i] != NULL; i++) {
        if (my_strlen(map[i]) > max)
            max = my_strlen(map[i]);
    }
    return max;
}

static int is_screen_size_enough(char **map)
{
    if (COLS < get_max_line_size(map) || LINES < my_array_len(map))
        return 0;
    return 1;
}

void display_screen(char **map)
{
    clear();
    if (!is_screen_size_enough(map)) {
        mvprintw(LINES / 2, COLS / 2 - 10, "Expand your terminal.");
        refresh();
        return;
    }
    for (int i = 0; map[i] != NULL; i++) {
        mvprintw(i, 0, "%s", map[i]);
    }
    refresh();
}
