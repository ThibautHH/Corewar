/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** st_op
*/

#include "corewar/corewar.h"

void st_op(vm_t *vm)
{
    uint8_t args_code = NEXT_BYTE;
    int32_t value;

    if (args_code & 0b1111u || args_code >> 6 != REG_CODE
        || !((args_code >> 4) & 0b11u)
        || ((args_code >> 4) & 0b11u) == DIR_CODE)
        return kill_process(vm);
    value = get_value(vm, REG_CODE, false, false);
    set_value(vm, (args_code >> 4) & 0b11u, value, false);
}
