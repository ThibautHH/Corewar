/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** utils
*/

#include "corewar/corewar.h"

uint32_t get_direct_value(process_t *process)
{
    uint32_t val = 0;

    for (uint8_t i = 0; i < 4; i++)
        val |= *(process->pc++) << (i * 8);
    return val;
}

uint32_t get_indirect_value(vm_t *vm, process_t *process)
{
    int16_t ind_value = 0;
    for (uint8_t i = 0; i < 2; i++)
        ind_value |= *(process->pc++) << (i * 8);
    ind_value %= IDX_MOD;

    uint32_t val = 0;
    for (uint8_t i = 0; i < 4; i++)
        val |= *(vm->memory + (\
        (process->pc - vm->memory + ind_value + i) % MEM_SIZE)) << (i * 8);
    return val;
}

void load_to_register(process_t *process, uint32_t value)
{
    int8_t reg_number = *(process->pc++);

    if (reg_number >= 1 && reg_number <= REG_NUMBER) {
        PROC_REG(process, reg_number) = value;
        process->carry = value == 0 ? 1 : 0;
    }
}

uint32_t get_arg_value(vm_t *vm, process_t *process, uint8_t arg_type)
{
    uint32_t value = 0;

    if (arg_type == T_REG)
        value = PROC_REG(process, *(process->pc++));
    if (arg_type == T_DIR)
        value = get_direct_value(process);
    if (arg_type == T_IND)
        value = get_indirect_value(vm, process);
    return value;
}
