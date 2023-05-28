/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** utils
*/

#include "corewar/corewar.h"
#include <stdio.h>
#include "ice/printf.h"

uint32_t get_direct_value(process_t *process)
{
    u_int32_t value = 0;
    int8_t reg_number;

    reg_number = *(process->pc++);
    if (reg_number >= 1 && reg_number <= REG_NUMBER)
        value = PROC_REG(process, reg_number);
    return value;
}

uint32_t get_indirect_value(vm_t *vm, process_t *process)
{
    int16_t ind_value = 0;
    for (uint8_t i = 0; i < 2; i++)
        ind_value |= *(process->pc++) << (i * 8);

    uint32_t val = 0;
    for (uint8_t i = 0; i < 4; i++) {
        if (process->pc - vm->memory + ind_value + i < 0)
            val |= *(vm->memory + (MEM_SIZE + (\
            (process->pc - vm->memory + ind_value + i\
            ) % MEM_SIZE))) << (i * 8);
        else
            val |= *(vm->memory + (\
                (process->pc - vm->memory + ind_value + i) % MEM_SIZE)\
                ) << (i * 8);
    }
    return val;
}

void load_to_register(process_t *process, uint32_t value)
{
    int8_t reg_number = *(process->pc++);

    if (reg_number >= 1 && reg_number <= REG_NUMBER)
        PROC_REG(process, reg_number) = value;
}

uint32_t get_register_value(process_t *process)
{
    uint8_t reg_index = *(process->pc++);
    uint32_t value = 0;

    for (uint8_t i = 0; i < 4; i++)
        if (reg_index >= 1 && reg_index <= REG_NUMBER)
            value |= *(process->regs->bytes + (\
                reg_index * REG_SIZE) + i) << (i * 8);
    return value;
}

uint32_t get_arg_value(vm_t *vm, process_t *process, uint8_t arg_type)
{
    uint32_t value = 0;

    if (arg_type == REG_CODE)
        value = get_register_value(process);
    if (arg_type == DIR_CODE)
        value = get_direct_value(process);
    if (arg_type == IND_CODE)
        value = get_indirect_value(vm, process);
    return value;
}
