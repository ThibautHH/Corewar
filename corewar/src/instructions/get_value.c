/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** get_value
*/

#include "corewar/corewar.h"

static int32_t get_register_value(vm_t *vm)
{
    uint8_t reg_num = NEXT_BYTE;

    if (reg_num < 1 || reg_num > REG_NUMBER) {
        kill_process(vm);
        return 0;
    }
    return PROC_REG(PROC, reg_num);
}

static int32_t get_direct_value(vm_t *vm, const bool is_index)
{
    register int32_t val = 0;

    for (register uint8_t i = 0; i < (is_index ? 2 : 4); i++)
        val |= NEXT_BYTE << (i * 8);
    return val;
}

static int32_t get_indirect_value(vm_t *vm, bool long_mode)
{
    ssize_t address = INST - vm->memory;
    int16_t offset = 0;
    int32_t value = 0;

    for (uint8_t i = 0; i < 2; i++)
        offset |= NEXT_BYTE << (i * 8);
    if (!long_mode)
        offset %= IDX_MOD;
    address += offset;
    if (address >= MEM_SIZE)
        address %= MEM_SIZE;
    else
        while (address < 0)
            address += MEM_SIZE;
    for (uint8_t i = 0; i < 4; i++)
        value |= vm->memory[address + i] << (i * 8);
    return value;
}

int32_t get_value(vm_t *vm, uint8_t type, bool is_index, bool long_mode)
{
    switch (type) {
    case REG_CODE:
        return get_register_value(vm);
    case DIR_CODE:
        return get_direct_value(vm, is_index);
    case IND_CODE:
        return get_indirect_value(vm, long_mode);
    default:
        kill_process(vm);
        return 0;
    }
}
