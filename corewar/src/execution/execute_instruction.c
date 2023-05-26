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

void zbui(UNUSED vm_t *vm, UNUSED champion_t *champ, UNUSED process_t *process)
{
    return;
}

static const instruction_t instructions[OP_TAB_SIZE] = {
    &live,
    &zbui,
    &zbui,
    &zbui,
    &zbui,
    &zbui,
    &zbui,
    &zbui,
    &zbui,
    &zbui,
    &zbui,
    &zbui,
    &zbui,
    &zbui,
    &zbui
    /*,
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
    if (!process->cycles_left) {
        if (((*process->pc) - 1) >= OP_TAB_SIZE)
            kill_process(vm, champ, process);
        else
            process->cycles_left = op_tab[(*process->pc) - 1].nbr_cycles;
        return;
    }
    if (!(--process->cycles_left))
        instructions[(*process->pc++) - 1](vm, champ, process);
}
