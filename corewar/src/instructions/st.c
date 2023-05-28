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

    if (args_code & 0b1111u || ARGT(1) != REG_CODE
        || !ARGT(2)
        || ARGT(2) == DIR_CODE)
        return kill_process(vm);
    value = get_value(vm, REG_CODE, false, false).direct;
    set_value(vm, ARGT(2), value, false);
}
