/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** get_filename.c
*/

#include <stdint.h>

#include "ice/string.h"

char *get_filename(char *filepath)
{
    uint64_t len = ice_strlen(filepath);

    if (len < 3 || ice_strcmp(filepath + len - 2, ".s"))
        return NULL;
    filepath[len - 2] = '\0';
    for (; len && filepath[len] != '/'; len--);
    return filepath + len + 1;
}
