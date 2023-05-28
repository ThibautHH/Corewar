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

static val_t get_direct_value(vm_t *vm, const bool is_index)
{
    register val_t val = {0};

    for (uint8_t i = 0, n = (is_index ? 2 : 4); i < n; i++)
        if (is_index)
            val.index |= NEXT_BYTE << BYTE_SHIFT;
        else
            val.direct |= NEXT_BYTE << BYTE_SHIFT;
    return val;
}

static int32_t get_indirect_value(vm_t *vm, bool long_mode)
{
    ssize_t address = INST - vm->memory;
    int16_t offset = 0;
    int32_t value = 0;

    for (uint8_t i = 0, n = 2; i < n; i++)
        offset |= NEXT_BYTE << BYTE_SHIFT;
    if (!long_mode)
        offset %= IDX_MOD;
    address += offset;
    if (address >= MEM_SIZE)
        address %= MEM_SIZE;
    else
        while (address < 0)
            address += MEM_SIZE;
    for (uint8_t i = 0, n = 4; i < n; i++)
        value |= vm->memory[address + i] << (i * 8);
    return value;
}

val_t get_value(vm_t *vm, uint8_t type, bool is_index, bool long_mode)
{
    switch (type) {
    case REG_CODE:
        return ((val_t){.direct = get_register_value(vm)});
    case DIR_CODE:
        return get_direct_value(vm, is_index);
    case IND_CODE:
        return ((val_t){.direct = get_indirect_value(vm, long_mode)});
    default:
        kill_process(vm);
        return ((val_t){0});
    }
}
