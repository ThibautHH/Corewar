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

void parse_args(int ac, char **av, vm_t *vm);
void print_all_champs(vm_t vm);
void is_champ_number_already_used(vm_t *vm, int number,
    champion_t *champion_origin);

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
    if (ac < 2 || (!ice_strcmp(av[1], "-h") || !ice_strcmp(av[1], "--help"))) {
        fwrite(help_message, 1, ice_strlen(help_message), stderr);
        return (0);
    } else {
        vm_t vm = {0};
        TAILQ_INIT(&vm.champ_list);
        parse_args(ac, av, &vm);
        print_all_champs(vm);

        champion_t *champion = NULL;
        TAILQ_FOREACH(champion, &vm.champ_list, entries)
            is_champ_number_already_used(&vm, champion->number, champion);

        if (vm.dump) {
            return (0);
        }

        return (0);
    }
}
