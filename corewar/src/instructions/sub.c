/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** sub
*/

#include "corewar/corewar.h"

void sub(UNUSED vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(process->pc++);
    if ((args_code >> 6) != REG_CODE || ((args_code >> 4) & 0x3) != REG_CODE
    || ((args_code >> 2) & 0x3) != REG_CODE)
        return;
    int8_t reg_number1 = *(process->pc++);
    int8_t reg_number2 = *(process->pc++);
    int8_t reg_number3 = *(process->pc++);
    if (reg_number1 < 1 || reg_number1 > REG_NUMBER || reg_number2 < 1
    || reg_number2 > REG_NUMBER || reg_number3 < 1 || reg_number3 > REG_NUMBER)
        return;
    uint32_t val1 = PROC_REG(process, reg_number1);
    uint32_t val2 = PROC_REG(process, reg_number2);
    uint32_t result = val1 - val2;
    PROC_REG(process, reg_number3) = result;
    process->carry = (result == 0) ? 1 : 0;
}
