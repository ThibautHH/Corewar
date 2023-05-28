/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** zjmp
*/

#include "corewar/corewar.h"

void zjmp(vm_t *vm)
{
    int16_t offset = get_value(vm, DIR_CODE, true, false).index;

    if (!PROC->carry)
        return;
    PROC->pc = INST;
    PROC->pc += offset;
    if (PROC->pc >= vm->memory + MEM_SIZE)
        do
            PROC->pc -= MEM_SIZE;
        while (PROC->pc >= vm->memory + MEM_SIZE);
    else
        while (PROC->pc < vm->memory)
            PROC->pc += MEM_SIZE;
}
