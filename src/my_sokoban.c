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
#include "include/my_io.h"
#include "include/my_std.h"
#include "my_sokoban.h"
#include "box.h"
#include "game.h"
#include "storage.h"
#include "player.h"
#include "position.h"
#include "utils.h"
#include "screen.h"

static int is_game_win(game_t *game)
{
    for (int i = 0; game->boxes[i] != NULL; i++) {
        if (game->boxes[i]->c != STORAGE_CHAR)
            return 0;
    }
    return 1;
}

static int is_game_loose(game_t *game)
{
    for (int i = 0; game->boxes[i] != NULL; i++) {
        if (is_box_stuck(game->map, game->boxes[i], game->player) == 1)
            return 1;
    }
    return 0;
}

game_state_t display_map(game_t *game)
{
    if (is_game_win(game) == 1) {
        return WIN;
    }
    if (is_game_loose(game) == 1) {
        return DEFEAT;
    }
    display_screen(game->map);
    return PLAYING;
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
    game->state = PLAYING;
    game->copy = make_game_copy(game);
    return game;
}

static void run_game_loop(game_t *game)
{
    int key = 0;

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    while (key != 'q') {
        if (key == ' ') {
            reset_game(game);
        }
        player_make_action(key, game, game->map);
        game->state = display_map(game);
        if (game->state == WIN || game->state == DEFEAT)
            break;
        key = getch();
    }
    endwin();
}

void display_usage(void)
{
    my_putstr("USAGE\n");
    my_putstr("    ./my_sokoban map\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("    map    file representing the warehouse map, containing ");
    my_putstr("'#' for walls,\n    'P' for the player, 'X' for boxes and 'O'");
    my_putstr(" for storage locations.\n");
}

int main(int ac, char **av)
{
    char **map = NULL;
    game_t *game = NULL;

    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        display_usage();
        return 84;
    }
    map = get_map(av[1]);
    if (map == NULL)
        return 84;
    game = create_game(map);
    if (game == NULL)
        return 84;
    run_game_loop(game);
    free_game(game);
    return game->state;
}
