/*
** EPITECH PROJECT, 2023
** my-sokoban
** File description:
** my_sokoban
*/

#include <ncurses.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/my_strings.h"
#include "include/my_std.h"

int main(int ac, char **av)
{
    char *buffer = NULL;
    char **map = NULL;

    buffer = file_to_buffer(av[1]);
    if (buffer == NULL)
        return 84;
    map = buffer_to_array(buffer, '\n');
    if (map == NULL)
        return 84;
    for (int i = 0; map[i] != NULL; i++)
        printf("%s\n", map[i]);
    free(buffer);
    my_freearray(map);
    return (0);
}
