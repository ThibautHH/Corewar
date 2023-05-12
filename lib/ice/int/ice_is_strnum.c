/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** ice_is_strnum
*/

#include <stdbool.h>
#include "ice/types.h"

bool ice_is_strnum(char const *str)
{
    if (!str)
        return (false);
    if (str[0] == '-')
        return (ice_is_strnum(str + 1));
    if (str[0] == '\0')
        return (false);
    for (uc_t i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return (false);
    return (true);
}
