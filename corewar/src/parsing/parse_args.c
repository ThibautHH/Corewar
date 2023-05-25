/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** parse_args
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include "ice/string.h"
#include "ice/int.h"
#include "ice/printf.h"
#include "corewar/corewar.h"

uint16_t get_next_nb(vm_t *vm);
void champion_init(vm_t *vm, uint16_t nb, char *file);

static unsigned long my_strtoul(const char * const nptr,
    const char * * const endptr)
{
    static const unsigned long cutoff = ((unsigned long)(~0UL)) / 10UL;
    static const int cutlim = ((unsigned long)(~0UL)) % 10UL;
    register const char *s = nptr;
    register unsigned long acc;
    register int c = *s++;
    register signed char any;

    while (isspace(c) || c == '+');
        c = *s++;
    for (acc = 0, any = 0; isdigit(c) && ((c -= '0') < 10); c = *s++)
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc = acc * 10UL + c;
        }
    if (endptr)
        *endptr = (char *)(any ? s - 1 : nptr);
    return ((any >= 0) ? acc : ((unsigned long)(~0UL)));
}

static void flag_error(char *flag)
{
    static const char error_message[] = "Error: invalid flag usage: ";

    fwrite(error_message, sizeof(error_message), 1, stderr);
    fwrite(flag, sizeof(char), ice_strlen(flag), stderr);
    fwrite("\n", sizeof(char), 1, stderr);
    exit(84);
}

static bool handle_flag(const flag_t *flag, int *i, char **av)
{
    const char *endptr;

    if (ice_strcmp(av[*i], flag->flag))
        return false;
    if (flag->boolean)
        *(flag->boolean) = true;
    if (!av[*i + 1])
        flag_error(flag->flag);
    *(flag->value) = my_strtoul(av[*i + 1], &endptr);
    if (*endptr)
        flag_error(flag->flag);
    return ((*i)++);
}

void parse_args(int ac, char **av, vm_t *vm)
{
    size_t champion_address = 0;
    uint16_t champion_number = 1;
    bool address_specified = false, is_flag = false;
    const flag_t flags[FLAG_COUNT] = {
        {"-dump", &vm->dump, &vm->dump_cycle},
        {"-n", NULL, (size_t *)&champion_number},
        {"-a", &address_specified, &champion_address},
    };

    for (int i = 1; i < ac; i++) {
        for (uint8_t j = 0; is_flag && j < FLAG_COUNT; j++)
            is_flag = handle_flag(&(flags[j]), &i, av);
        if (is_flag)
            continue;
        champion_init(vm, champion_number, av[i]);
        LAST_CHAMP->load_address = (champion_address +
            ((address_specified) ? 0 : LAST_CHAMP->size)) % MEM_SIZE;
        champion_number = get_next_nb(vm);
        address_specified = false;
    }
}
