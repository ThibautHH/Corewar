/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** add_sub
*/

#include "corewar/corewar.h"

void add(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    int32_t reg_values[2];

    if (args_code != 0b01010100u)
        return kill_process(vm);
    for (uint8_t i = 0; i < 2; i++)
        reg_values[i] = get_value(vm, REG_CODE, false, false).direct;
    set_value(vm, REG_CODE, reg_values[0] + reg_values[1], true);
}

void sub(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    int32_t reg_values[2];

    if (args_code != 0b01010100u)
        return kill_process(vm);
    for (uint8_t i = 0; i < 2; i++)
        reg_values[i] = get_value(vm, REG_CODE, false, false).direct;
    set_value(vm, REG_CODE, reg_values[0] - reg_values[1], true);
}
