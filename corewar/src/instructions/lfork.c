/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** lfork
*/

#include "corewar/corewar.h"
#include "ice/memory.h"

void lfork(vm_t *vm)
{
    int32_t offset = get_value(vm, DIR_CODE, true, false);
    process_t *new_proc = malloc(sizeof(process_t));

    if (!new_proc)
        exit(84);
    *new_proc = *PROC;
    new_proc->pc += offset;
    if (new_proc->pc >= vm->memory + MEM_SIZE)
        do
            new_proc->pc -= MEM_SIZE;
        while (new_proc->pc >= vm->memory + MEM_SIZE);
    else
        while (new_proc->pc < vm->memory)
            new_proc->pc += MEM_SIZE;
    TAILQ_INSERT_HEAD(&CHAMP->process_list, new_proc, entries);
}
