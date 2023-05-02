/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** parse_args
*/

#include <stdio.h>
#include "ice/string.h"
#include "ice/int.h"
#include "ice/printf.h"
#include "corewar/corewar.h"

static int check_if_args_aberations(int ac, char **av)
{
    for (int i = 1; i < ac; i++) {
        if (!ice_strcmp(av[i], "-dump")
            && (i + 1 >= ac || !IS_STR_NUM(av[i + 1])))
            return 1;
        if (!ice_strcmp(av[i], "-n")
            && (i + 1 >= ac || !IS_STR_NUM(av[i + 1])))
            return 1;
        if (!ice_strcmp(av[i], "-a")
            && (i + 1 >= ac || !IS_STR_NUM(av[i + 1])))
            return 1;
    }
    return 0;
}

static int check_if_args_files(int ac, char **av)
{
    for (int i = 1; i < ac; i++) {
        if (!ice_strcmp(av[i], "-dump") || !ice_strcmp(av[i], "-n")
            || !ice_strcmp(av[i], "-a")) {
            i += (i + 1 < ac) ? 1 : 0;
            continue;
        }
        FILE *file = fopen(av[i], "r");
        if (!file) {
            ice_printf("Invalid file: %s\n", av[i]);
            return 1;
        }
        fclose(file);
    }
    return 0;
}

int parse_arg(corewar_t *corewar, int ac, char **av)
{
    if (check_if_args_aberations(ac, av) || check_if_args_files(ac, av))
        return 1;
    for (int i = 1; i < ac; i++) {
        if (!ice_strcmp(av[i], "-dump")) {
            (corewar->arg_parse.dump = (i + 1 < ac)
                ? ice_atoi(av[i + 1]) : 0);
            i += (i + 1 < ac) ? 1 : 0;
        }
        if (!ice_strcmp(av[i], "-n")) {
            corewar->arg_parse.prog_number = (i + 1 < ac)
                ? ice_atoi(av[i + 1]) : 0;
            i += (i + 1 < ac) ? 1 : 0;
        }
        if (!ice_strcmp(av[i], "-a")) {
            corewar->arg_parse.load_address = (i + 1 < ac)
                ? ice_atoi(av[i + 1]) : 0;
            i += (i + 1 < ac) ? 1 : 0;
        }
    }
    return 0;
}
