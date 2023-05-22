/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** is_nbr
*/

#include "corewar/corewar.h"

bool is_nbr(char *str)
{
    if (!str)
        return (false);
    for (size_t i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (false);
    }
    return (true);
}
