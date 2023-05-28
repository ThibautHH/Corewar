/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** lld
*/

#include "corewar/corewar.h"

void lld(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    uint32_t value;

    if (args_code & 0b1111u || ARGT(2) != 0b01u
        || !ARGT(1) || ARGT(1) == REG_CODE)
        return kill_process(vm);
    value = get_value(vm, ARGT(1) & 0b11u, false, true).direct;
    set_value(vm, REG_CODE, value, true);
}
