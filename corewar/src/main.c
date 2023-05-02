/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** main.c
*/

#include <stdio.h>
#include "ice/string.h"
#include "ice/printf.h"
#include <malloc.h>
#include "corewar/corewar.h"

static const char *help_message =
"USAGE\n"
"./corewar"
"[-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] ...\n"
"DESCRIPTION\n"
"-dump nbr_cycle dumps the memory after the nbr_cycle execution (if the round"
"isn't already over) with the following format: 32 bytes/line in hexadecimal"
"(A0BCDEFE1DD3...)\n"
"-n prog_number sets the next program's number. By default, the first free"
"number in the parameter order\n"
"-a load_address sets the next program's loading address. When no address is"
"specified, optimize the addresses so that the processes are as far"
"away from each other as possible. The addresses are MEM_SIZE modulo.\n";

int main(int ac, char **av)
{
    corewar_t *corewar;

    if (ac == 2
        && (!ice_strcmp(av[1], "-h") || !ice_strcmp(av[1], "--help"))) {
        ice_printf("%s", help_message);
        return 0;
    } else if (ac < 2) {
        ice_printf("Usage: %s [-h | --help]\n", av[0]);
        return 84;
    }
    corewar = malloc(sizeof(corewar_t));
    if (parse_arg(corewar, ac, av)) {
        ice_printf("Invalid argument, use -h or --help for more information\n");
        free(corewar);
        return 84;
    }
    return 0;
}
