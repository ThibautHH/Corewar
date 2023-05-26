/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** execute_instruction
*/

#include <stdio.h>
#include "corewar/corewar.h"
#include "ice/memory.h"
#include "ice/printf.h"

void live(vm_t *vm, champion_t *champ, process_t *process);
void ld_op(vm_t *vm, champion_t *champ, process_t *process);
void st_op(vm_t *vm, champion_t *champ, process_t *process);
void add(vm_t *vm, champion_t *champ, process_t *process);
void sub(vm_t *vm, champion_t *champ, process_t *process);
void and_op(vm_t *vm, champion_t *champ, process_t *process);
void or_op(vm_t *vm, champion_t *champ, process_t *process);
void xor_op(vm_t *vm, champion_t *champ, process_t *process);
void zjmp(vm_t *vm, champion_t *champ, process_t *process);
void ldi(vm_t *vm, champion_t *champ, process_t *process);
void sti(vm_t *vm, champion_t *champ, process_t *process);
void fork_op(vm_t *vm, champion_t *champ, process_t *process);
void lld(vm_t *vm, champion_t *champ, process_t *process);
void lldi(vm_t *vm, champion_t *champ, process_t *process);
void lfork(vm_t *vm, champion_t *champ, process_t *process);
void aff(vm_t *vm, champion_t *champ, process_t *process);

static const instruction_t instructions[OP_TAB_SIZE] = {
    &live,
    &ld_op,
    &st_op,
    &add,
    &sub,
    &and_op,
    &or_op,
    &xor_op,
    &zjmp,
    &ldi,
    &sti,
    &fork_op,
    &lld,
    &lldi,
    &lfork,
    &aff
};

void kill_process(vm_t *vm, champion_t *champ, process_t *process)
{
    TAILQ_REMOVE(&champ->process_list, process, entries);
    vm->nb_process--;
    free(process);
    if (TAILQ_EMPTY(&champ->process_list)) {
        ice_printf("The player %d(%s)has died.\n", champ->number, champ->name);
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
