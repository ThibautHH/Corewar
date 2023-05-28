/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** lldi
*/

#include "corewar/corewar.h"

void lldi(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    int32_t vals[2];
    ssize_t address = INST - vm->memory;
    int32_t value;

    if (!(args_code >> 6) || ((args_code >> 4) & 0b11u) == 0b11u
        || !((args_code >> 4) & 0b11u)
        || ((args_code >> 2) & 0b11u) != REG_CODE || (args_code & 0b11u))
        return kill_process(vm);
    vals[0] = get_value(vm, args_code >> 6, true, true);
    vals[1] = get_value(vm, (args_code >> 4) & 0b11u, true, true);
    address += (vals[0] + vals[1]) % IDX_MOD;
    if (address >= MEM_SIZE)
        address %= MEM_SIZE;
    else
        while (address < 0)
            address += MEM_SIZE;
    for (uint8_t i = 0; i < 4; i++)
        value |= vm->memory[address + i] << (i * 8);
    set_value(vm, REG_CODE, value, true);
}
