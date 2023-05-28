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

#if defined(DEBUG)
void instructions_debug(champion_t *champ, op_t op);
#endif

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

size_t get_arg_length(uint8_t args_code, uint8_t arg_index)
{
    uint8_t arg_type = (args_code >> ((3 - arg_index) * 2)) & 0x3;

    if (arg_type == REG_CODE)
        return REG_SIZE;
    if (arg_type == DIR_CODE)
        return DIR_SIZE;
    if (arg_type == IND_CODE)
        return IND_SIZE;
    return 0;
}

void execute_instruction(vm_t *vm, champion_t *champ, process_t *process)
{
    if (process->pc == NULL) return;
    uint8_t opcode = *process->pc;
    if (opcode < 1 || opcode > OP_TAB_SIZE) return;
    op_t op = op_tab[opcode - 1];
    size_t length = op.nbr_args;
    for (uint8_t i = 0; i < op.nbr_args; i++)
        length += get_arg_length(*(process->pc + 1), i);
    (length == 0) ? NEXT_BYTE : 0;
    if (length == 0) return;
#if defined(DEBUG)
    instructions_debug(champ, op);
#endif
    if (process->cycles_left == 0) {
        process->cycles_left = op.nbr_cycles;
        if (op.code >= 1 && op.code <= 16)
            instructions[op.code - 1](vm, champ, process);
        process->pc += length;
    } else
        process->cycles_left--;
}
