/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** ld_op
*/

#include "corewar/corewar.h"

void ld_op(vm_t *vm)
{
    uint8_t args_code = *(PROC->pc++);
    uint32_t value;

    if (args_code & 0b1111u || ((args_code >> 4) & 0b11u) != 0b01u
        || !(args_code >> 6) || ((args_code >> 6) & 0b11u) == REG_CODE)
        return kill_process(vm);
    value = get_value(vm, (args_code >> 6) & 0b11u, false, false);
    set_value(vm, REG_CODE, value, true);
}
