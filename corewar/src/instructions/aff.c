/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** aff
*/

#include <stdio.h>
#include "corewar/corewar.h"

void aff(vm_t *vm)
{
    char c;

    if (NEXT_BYTE != 0b10000000u)
        return kill_process(vm);
    c = (char)(PROC_REG(PROC, (*(PROC->pc++)) % 256));
    fwrite(&c, sizeof(char), 1, stdout);
}
