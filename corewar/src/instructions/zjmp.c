/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** zjmp
*/

#include "corewar/corewar.h"

void zjmp(vm_t *vm)
{
    int32_t offset = get_value(vm, DIR_CODE, true, false);

    if (!PROC->carry)
        return;
    PROC->pc += offset % IDX_MOD;
    if (PROC->pc >= vm->memory + MEM_SIZE)
        do
            PROC->pc -= MEM_SIZE;
        while (PROC->pc >= vm->memory + MEM_SIZE);
    else
        while (PROC->pc < vm->memory)
            PROC->pc += MEM_SIZE;
}
