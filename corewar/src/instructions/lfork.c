/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** lfork
*/

#include "corewar/corewar.h"
#include "ice/memory.h"

static int16_t get_direct_value_short(process_t *process)
{
    int16_t val = 0;

    for (uint8_t i = 0; i < 2; i++)
        val |= *(process->pc++) << (i * 8);

    return val;
}

static process_t *clone_process(process_t *process, int16_t offset)
{
    process_t *new_process = malloc(sizeof(process_t));

    if (new_process != NULL) {
        ice_memcpy(new_process, process, sizeof(process_t));
        new_process->pc = process->pc + offset;
    }

    return new_process;
}

static void add_process(UNUSED vm_t *vm, process_t *process, champion_t *champ)
{
    process_t *new_process = malloc(sizeof(process_t));

    if (new_process != NULL) {
        ice_memcpy(new_process, process, sizeof(process_t));
        new_process->pc = process->pc + get_direct_value_short(process);
        new_process->carry = process->carry;
        new_process->cycles_left = 0;
        new_process->regs[0] = process->regs[0];
        for (uint8_t i = 1; i < REG_NUMBER; i++)
            new_process->regs[i] = process->regs[i];
        TAILQ_INSERT_TAIL(&champ->process_list, new_process, entries);
    }
}

void lfork(vm_t *vm, champion_t *champ, process_t *process)
{
    int16_t direct_value = get_direct_value_short(process);

    UNUSED process_t *new_process = clone_process(process, direct_value);
    add_process(vm, process, champ);
}
