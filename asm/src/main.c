/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** main.c
*/
#include "corewar/asm.h"

int main(int ac, char **av)
{
    return (ac == 2 && run_asm(av[1])) ? 0 : 84;
}
