/*
** EPITECH PROJECT, 2023
** my-sokoban [WSL: Ubuntu]
** File description:
** position
*/

int get_pos_in_buffer(char *buffer, char c)
{
    int i = 0;

    for (; buffer[i] != '\0'; i++)
        if (buffer[i] == c)
            return i;
    return -1;
}
