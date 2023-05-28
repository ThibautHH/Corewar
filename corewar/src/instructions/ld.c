/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** ld_op
*/

#include "corewar/corewar.h"

void ld_op(vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(NEXT_BYTE);
    uint32_t first_arg_value = ((args_code >> 6) == T_DIR)
        ? get_direct_value(vm, process)
        : get_indirect_value(vm, process);

    if (((args_code >> 4) & 0x3) == REG_CODE)
        load_to_register(vm, process, first_arg_value);
}
