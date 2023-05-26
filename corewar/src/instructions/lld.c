/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** lld
*/

#include "corewar/corewar.h"

static uint32_t get_indirect_value_without_mod(vm_t *vm, process_t *process)
{
    int16_t ind_value = 0;
    for (uint8_t i = 0; i < 2; i++)
        ind_value |= *(process->pc++) << (i * 8);

    uint32_t val = 0;
    for (uint8_t i = 0; i < 4; i++)
        val |= *(vm->memory + (\
            (process->pc - vm->memory + ind_value + i) % MEM_SIZE)) << (i * 8);
    return val;
}

void lld(vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(process->pc++);
    uint32_t first_arg_value = 0;

    if ((args_code >> 6) == T_DIR) {
        first_arg_value = get_direct_value(process);
    } else {
        first_arg_value = get_indirect_value_without_mod(vm, process);
    }

    if (((args_code >> 4) & 0x3) == REG_CODE) {
        load_to_register(process, first_arg_value);
    }
}
