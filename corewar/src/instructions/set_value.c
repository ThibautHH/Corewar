/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** set_value
*/

#include "corewar/corewar.h"

static void set_register_value(vm_t *vm, int32_t value, bool set_carry)
{
    uint8_t reg_num = NEXT_BYTE;

    if (reg_num < 1 || reg_num > REG_NUMBER)
        return kill_process(vm);
    PROC_REG(PROC, reg_num) = value;
    if (set_carry)
        PROC->carry = (!value);
}

static void set_indirect_value(vm_t *vm, int32_t value)
{
    ssize_t address = INST - vm->memory;
    int16_t offset = 0;

    for (uint8_t i = 0; i < 2; i++)
        offset |= NEXT_BYTE << (i * 8);
    offset %= IDX_MOD;
    address += offset;
    if (address >= MEM_SIZE)
        address %= MEM_SIZE;
    else
        while (address < 0)
            address += MEM_SIZE;
    for (uint8_t i = 0; i < 4; i++)
        vm->memory[address + i] = (value >> (i * 8)) & 0xFF;
}

void set_value(vm_t *vm, uint8_t type, int32_t value, bool set_carry)
{
    switch (type) {
    case REG_CODE:
        return set_register_value(vm, value, set_carry);
    case IND_CODE:
        return set_indirect_value(vm, value);
    default:
        return kill_process(vm);
    }
}
