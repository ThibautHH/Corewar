/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** sti
*/

#include "corewar/corewar.h"

void sti(vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(process->pc++);
    int32_t first_arg_value = 0;
    int32_t second_arg_value = 0;
    int32_t third_arg_value = 0;

    first_arg_value = get_arg_value(vm, process, args_code >> 6);
    second_arg_value = get_arg_value(vm, process, (args_code >> 4) & 0x3);
    third_arg_value = get_arg_value(vm, process, (args_code >> 2) & 0x3);

    int32_t sum = (second_arg_value + third_arg_value) % IDX_MOD;

    for (uint8_t i = 0; i < 4; i++) {
        *(vm->memory + ((process->pc - vm->memory + sum + i) % MEM_SIZE)) = (\
            first_arg_value >> (i * 8)) & 0xFF;
    }
}
