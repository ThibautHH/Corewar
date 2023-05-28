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
    int16_t vals[2];
    ssize_t address = INST - vm->memory;
    int32_t value;

    if (!ARGT(1) || ARGT(2) == 0b11u
        || !ARGT(2) || ARGT(3) != REG_CODE || ARGT(4))
        return kill_process(vm);
    vals[0] = get_value(vm, ARGT(1), true, true).index;
    vals[1] = get_value(vm, ARGT(2), true, true).index;
    address += (vals[0] + vals[1]) % IDX_MOD;
    if (address >= MEM_SIZE)
        address %= MEM_SIZE;
    else
        while (address < 0)
            address += MEM_SIZE;
    for (uint8_t i = 0, n = 4; i < n; i++)
        value |= vm->memory[address + i] << (i * 8);
    set_value(vm, REG_CODE, value, true);
}
