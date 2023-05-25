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

void parse_args(int ac, char **av, vm_t *vm);
#if defined(DEBUG)
    void print_debug(vm_t *vm);
#endif
void vm_init(vm_t *vm);
void vm_setup(vm_t *vm);

static const char help_message[] = "USAGE\n"
    "./corewar "
    "[-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] ...\n"
    "DESCRIPTION\n"
    "-dump nbr_cycle dumps the memory after the nbr_cycle execution "
    "(if the round isn't already over) with the following format: "
    "32 bytes/line\n"
    "in hexadecimal (A0BCDEFE1DD3...)\n"
    "-n prog_number sets the next program's number. By default, the first free"
    " number in the parameter order\n"
    "-a load_address sets the next program's loading address. When no address "
    "is specified, optimize the addresses so that the processes are as far "
    "away from each other as possible. The addresses are MEM_SIZE modulo.\n";

int main(int ac, char **av)
{
    vm_t vm = {0};

    if (ac < 2 || (!ice_strcmp(av[1], "-h") || !ice_strcmp(av[1], "--help"))) {
        fwrite(help_message, sizeof(help_message), 1,
            ((ac < 2) ? stderr : stdout));
        return ((ac < 2) ? 84 : 0);
    }
    vm_init(&vm);
    parse_args(ac, av, &vm);
    vm_setup(&vm);
    return (0);
}
