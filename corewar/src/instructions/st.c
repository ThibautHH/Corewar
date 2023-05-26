/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** st_op
*/

#include "corewar/corewar.h"

void st_op(vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(process->pc++);
    int8_t reg_number;
    if ((args_code >> 6) != REG_CODE)
        return;
    reg_number = *(process->pc++);
    if (reg_number < 1 || reg_number > REG_NUMBER)
        return;
    uint32_t reg_value = PROC_REG(process, reg_number);
    if (((args_code >> 4) & 0x3) == REG_CODE)
        load_to_register(process, reg_value);
    if (((args_code >> 4) & 0x3) == IND_CODE) {
        int16_t ind_value = 0;
        for (uint8_t i = 0; i < 2; i++)
            ind_value |= *(process->pc++) << (i * 8);
        ind_value %= IDX_MOD;
        for (uint8_t i = 0; i < 4; i++)
            *(vm->memory + ((process->pc - vm->memory + ind_value + i\
                ) % MEM_SIZE)) = (reg_value >> (i * 8)) & 0xFF;
    }
}
