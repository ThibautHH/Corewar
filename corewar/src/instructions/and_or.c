/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** and_op
*/

#include "corewar/corewar.h"

void and_op(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    int32_t vals[2];

    if (ARGT(4) || ARGT(3) != 0b01u
        || !ARGT(2) || !ARGT(1))
        return kill_process(vm);
    for (uint8_t i = 0; i < 2; i++)
        vals[i] = get_value(vm, ARGT(i + 1), false, false).direct;
    set_value(vm, REG_CODE, vals[0] & vals[1], true);
}

void or_op(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    int32_t vals[2];

    if (ARGT(4) || ARGT(3) != 0b01u
        || !ARGT(2) || !ARGT(1))
        return kill_process(vm);
    for (uint8_t i = 0; i < 2; i++)
        vals[i] = get_value(vm, ARGT(i + 1), false, false).direct;
    set_value(vm, REG_CODE, vals[0] | vals[1], true);
}

void xor_op(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    int32_t vals[2];

    if (ARGT(4) || ARGT(3) != 0b01u
        || !ARGT(2) || !ARGT(1))
        return kill_process(vm);
    for (uint8_t i = 0; i < 2; i++)
        vals[i] = get_value(vm, ARGT(i + 1), false, false).direct;
    set_value(vm, REG_CODE, vals[0] ^ vals[1], true);
}
