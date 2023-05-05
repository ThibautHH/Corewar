/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** main.c
*/
#include "corewar/asm.h"

int main(int ac, char **av)
{
    return (ac == 2 && asm_f(av[1])) ? 0 : 84;
}
