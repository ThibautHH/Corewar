/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** fork
*/

#include <stdio.h>
#include "corewar/corewar.h"

void fork_op(vm_t *vm, champion_t *champ, process_t *process)
{
    uint16_t ind_value = 0;
    for (uint8_t i = 0; i < 2; i++)
        ind_value |= *(process->pc++) << (i * 8);
    ind_value %= IDX_MOD;

    process_t *new_process = malloc(sizeof(process_t));
    if (!new_process) {
        fwrite("Malloc error\n", 1, 13, stderr);
        exit(84);
    }
    new_process->pc = vm->memory + (\
        process->pc - vm->memory + ind_value) % MEM_SIZE;
    new_process->carry = process->carry;
    new_process->cycles_left = 0;
    new_process->regs[0] = process->regs[0];
    for (uint8_t i = 1; i < REG_NUMBER; i++)
        new_process->regs[i] = process->regs[i];
    TAILQ_INSERT_TAIL(&champ->process_list, new_process, entries);
}
