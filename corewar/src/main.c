/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** main.c
*/

#include <stdio.h>
#include "ice/string.h"
#include "ice/printf.h"
#include "corewar/corewar.h"

int main(int ac, char **av)
{
    FILE *file;

    if (ac == 2 && (!ice_strcmp(av[1], "-h") || !ice_strcmp(av[1], "--help")))
        ice_printf(HELP_MESSAGE);
    return 0;
}
