/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** ldi
*/

#include "corewar/corewar.h"

void ldi(vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(process->pc++);
    int32_t first_arg_value = 0;
    int32_t second_arg_value = 0;

    first_arg_value = get_arg_value(vm, process, args_code >> 6);
    second_arg_value = get_arg_value(vm, process, (args_code >> 4) & 0x3);

    int32_t sum = (first_arg_value + second_arg_value) % IDX_MOD;
    int32_t value_to_load = 0;
    for (uint8_t i = 0; i < 4; i++) {
        value_to_load |= *(vm->memory + (\
            (process->pc - vm->memory + sum + i) % MEM_SIZE)) << (i * 8);
    }

    if (((args_code >> 2) & 0x3) == REG_CODE)
        load_to_register(process, value_to_load);
}
