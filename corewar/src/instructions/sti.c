/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** sti
*/

#include "corewar/corewar.h"

void sti(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    int32_t value;
    int32_t vals[2];
    ssize_t address = INST - vm->memory;

    if (!((args_code >> 2) & 0b11u) || ((args_code >> 2) & 0b11u) == IND_CODE
        || !((args_code >> 4) & 0b11u)
        || args_code >> 6 != REG_CODE || (args_code & 0b11u))
        return kill_process(vm);
    value = get_value(vm, REG_CODE, true, false);
    vals[0] = get_value(vm, (args_code >> 4) & 0b11u, true, false);
    vals[1] = get_value(vm, (args_code >> 2) & 0b11u, true, false);
    address += (vals[0] + vals[1]) % IDX_MOD;
    if (address >= MEM_SIZE)
        address %= MEM_SIZE;
    else
        while (address < 0)
            address += MEM_SIZE;
    for (uint8_t i = 0; i < 4; i++)
        vm->memory[address + i] = (value >> (i * 8)) & 0xFFu;
}
