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

void live(vm_t *vm);
void ld_op(vm_t *vm);
void st_op(vm_t *vm);
void add(vm_t *vm);
void sub(vm_t *vm);
void and_op(vm_t *vm);
void or_op(vm_t *vm);
void xor_op(vm_t *vm);
void zjmp(vm_t *vm);
void ldi(vm_t *vm);
void sti(vm_t *vm);
void fork_op(vm_t *vm);
void lld(vm_t *vm);
void lldi(vm_t *vm);
void lfork(vm_t *vm);
void aff(vm_t *vm);

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

void kill_process(vm_t *vm)
{
    TAILQ_REMOVE(&CHAMP->process_list, PROC, entries);
    vm->nb_process--;
    free(PROC);
    if (TAILQ_EMPTY(&CHAMP->process_list)) {
        ice_printf("The player %d(%s)has died.\n", CHAMP->number, CHAMP->name);
        TAILQ_REMOVE(&vm->champ_list, CHAMP, entries);
        vm->nb_champ--;
        free(CHAMP->code);
        free(CHAMP);
    }
}

void execute_instructon(vm_t *vm)
{
    uint8_t code = (*PROC->pc) - 1;

    if (code >= OP_TAB_SIZE)
        return kill_process(vm);
    if (!PROC->cycles_left) {
        PROC->cycles_left = op_tab[code].nbr_cycles;
        return;
    }
    if (!(--PROC->cycles_left)) {
        INST = PROC->pc++;
        instructions[code](vm);
    }
}
