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
#include "box.h"
#include "storage.h"
#include "player.h"
#include "position.h"

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

void display_map(char **map, player_t *player)
{
    for (int i = 0; map[i] != NULL; i++) {
        for (int j = 0; map[i][j] != '\0'; j++) {
            mvprintw(i, j, "%c", map[i][j]);
        }
    }
}

static game_t *create_game(char **map)
{
    game_t *game = malloc(sizeof(game_t));

    if (game == NULL)
        return NULL;
    game->map = map;
    game->player = create_player(map);
    if (game->player == NULL)
        return NULL;
    game->nb_boxes = get_pos_count(map, BOX_CHAR);
    game->boxes = create_boxes(map, game->nb_boxes);
    if (game->boxes == NULL)
        return NULL;
    game->nb_storages = get_pos_count(map, STORAGE_CHAR);
    game->storages = create_storages(map, game->nb_storages);
    if (game->storages == NULL)
        return NULL;
    return game;
}

static int run_game_loop(game_t *game)
{
    int key = 0;

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    while (key != 'q') {
        player_make_action(key, game, game->map);
        display_map(game->map, game->player);
        refresh();
        key = getch();
    }
    endwin();
    return EXIT_SUCCESS;
}

int main(int ac, char **av)
{
    char **map = NULL;
    game_t *game = NULL;

    map = get_map(av[1]);
    if (map == NULL)
        return 84;
    game = create_game(map);
    if (game == NULL)
        return 84;
    if (run_game_loop(game) == EXIT_FAILURE)
        return 84;
    free_game(game);
    return EXIT_SUCCESS;
}
