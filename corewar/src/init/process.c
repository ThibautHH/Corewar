/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** process
*/

#include "corewar/corewar.h"
#include "ice/memory.h"

void process_init(vm_t *vm, champion_t *champ)
{
    process_t *process = malloc(sizeof(process_t));

    if (!process)
        exit(84);
    process->carry = 0;
    process->pc = vm->memory + champ->load_address;
    ice_memset(process->regs, 0, REG_SIZE * REG_NUMBER);
    PROC_REG(process, 1) = champ->number;
    TAILQ_INSERT_TAIL(&champ->process_list, process, entries);
    vm->nb_process++;
}
