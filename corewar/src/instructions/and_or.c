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

    if (args_code & 0b11u || ((args_code >> 2) & 0b11u) != 0b01u
        || !((args_code >> 4) & 0b11u) || !(args_code >> 6))
        return kill_process(vm);
    for (uint8_t i = 0; i < 2; i++)
        vals[i] = get_value(vm, (args_code >> (6 - i * 2)) & 0b11u, false,
            false);
    set_value(vm, REG_CODE, vals[0] & vals[1], true);
}

void or_op(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    int32_t vals[2];

    if (args_code & 0b11u || ((args_code >> 2) & 0b11u) != 0b01u
        || !((args_code >> 4) & 0b11u) || !(args_code >> 6))
        return kill_process(vm);
    for (uint8_t i = 0; i < 2; i++)
        vals[i] = get_value(vm, (args_code >> (6 - i * 2)) & 0b11u, false,
            false);
    set_value(vm, REG_CODE, vals[0] | vals[1], true);
}

void xor_op(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    int32_t vals[2];

    if (args_code & 0b11u || ((args_code >> 2) & 0b11u) != 0b01u
        || !((args_code >> 4) & 0b11u) || !(args_code >> 6))
        return kill_process(vm);
    for (uint8_t i = 0; i < 2; i++)
        vals[i] = get_value(vm, (args_code >> (6 - i * 2)) & 0b11u, false,
            false);
    set_value(vm, REG_CODE, vals[0] ^ vals[1], true);
}
