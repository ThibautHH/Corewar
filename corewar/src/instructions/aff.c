/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** aff
*/

#include <stdio.h>
#include "corewar/corewar.h"

void aff(vm_t *vm, champion_t *champ, process_t *process)
{
    char c = (char)(PROC_REG(process, (*(++process->pc)) % 256));

    fwrite(&c, sizeof(char), 1, stdout);
}
