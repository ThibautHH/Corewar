/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** process
*/

#include "corewar/corewar.h"
#include "ice/memory.h"

void process_init(process_t *process, size_t pc)
{
    ice_memset(process->reg, 0, sizeof(process->reg));
    process->carry = 0;
    process->pc = pc;
}
