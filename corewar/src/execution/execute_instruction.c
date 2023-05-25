/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** execute_instruction
*/

#include <stdio.h>
#include "corewar/corewar.h"
#include "ice/memory.h"

void live(vm_t *vm, champion_t *champ, process_t *process);

static const instruction_t instructions[OP_TAB_SIZE] = {
    &live/*,
    &ld,
    &st,
    &add,
    &sub,
    &and,
    &or,
    &xor,
    &zjmp,
    &ldi,
    &sti,
    &fork,
    &lld,
    &lldi,
    &lfork,
    &aff*/
};

void kill_process(vm_t *vm, champion_t *champ, process_t *process)
{
    TAILQ_REMOVE(&champ->process_list, process, entries);
    vm->nb_process--;
    free(process);
    if (TAILQ_EMPTY(&champ->process_list)) {
        TAILQ_REMOVE(&vm->champ_list, champ, entries);
        vm->nb_champ--;
        free(champ->code);
        free(champ);
    }
}

void execute_instructon(vm_t *vm, champion_t *champ, process_t *process)
{
    if (*process->pc >= OP_TAB_SIZE)
        kill_process(vm, champ, process);
    if (process->cycles_left) {
        process->cycles_left--;
        return;
    }
    process->cycles_left = op_tab[*process->pc].nbr_cycles;
    instructions[*(process->pc++)](vm, champ, process);
}
