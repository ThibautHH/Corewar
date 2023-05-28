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
    int16_t value;
    int16_t vals[2];
    ssize_t address = INST - vm->memory;

    if (!ARGT(3) || ARGT(3) == IND_CODE || !ARGT(2)
        || ARGT(1) != REG_CODE || ARGT(4))
        return kill_process(vm);
    value = get_value(vm, REG_CODE, true, false).index;
    vals[0] = get_value(vm, ARGT(2), true, false).index;
    vals[1] = get_value(vm, ARGT(3), true, false).index;
    address += (vals[0] + vals[1]) % IDX_MOD;
    if (address >= MEM_SIZE)
        address %= MEM_SIZE;
    else
        while (address < 0)
            address += MEM_SIZE;
    for (uint8_t i = 0, n = 4; i < n; i++)
        vm->memory[address + i] = (value >> BYTE_SHIFT) & 0xFFu;
}
