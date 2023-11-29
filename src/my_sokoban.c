/*
** EPITECH PROJECT, 2023
** my-sokoban
** File description:
** my_sokoban
*/

#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/my_strings.h"
#include "include/my_std.h"
#include "my_sokoban.h"
#include "player.h"

static void free_game(game_t *game)
{
    free(game->player->pos);
    free(game->player);
    my_freearray(game->map);
    free(game);
}

static char **get_map(char *filepath)
{
    char *buffer = NULL;
    char **map = NULL;

    buffer = file_to_buffer(filepath);
    if (buffer == NULL)
        return NULL;
    map = buffer_to_array(buffer, '\n');
    free(buffer);
    if (map == NULL)
        return NULL;
    return map;
}

void update_player_in_map(player_t *player, char **map, int i, int j)
{
    if (i == player->pos->y && j == player->pos->x)
        mvprintw(i, j, "%c", PLAYER_CHAR);
    else
        mvprintw(i, j, "%c", map[i][j]);
}

void display_map(char **map, player_t *player)
{
    for (int i = 0; map[i] != NULL; i++) {
        for (int j = 0; map[i][j] != '\0'; j++) {
            update_player_in_map(player, map, i, j);
        }
    }
}

static int run_game_loop(game_t *game)
{
    int key = 0;

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    while (key != 'q') {
        move_player(key, game->player, game->map);
        display_map(game->map, game->player);
        refresh();
        key = getch();
    }
    endwin();
    return EXIT_SUCCESS;
}

int main(int ac, char **av)
{
    int key = 0;
    game_t *game = malloc(sizeof(game_t));

    if (game == NULL)
        return 84;
    game->map = get_map(av[1]);
    if (game->map == NULL)
        return 84;
    game->player = create_player(game->map);
    if (game->player == NULL)
        return 84;
    if (run_game_loop(game) == EXIT_FAILURE)
        return 84;
    free_game(game);
    return EXIT_SUCCESS;
}
