/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** and_op
*/

#include "corewar/corewar.h"

static uint32_t get_value_from_type(vm_t *vm, process_t *process, uint8_t type)
{
    uint32_t value = 0;
    int8_t reg_number;

    if (type == REG_CODE) {
        reg_number = *(process->pc++);
        value = PROC_REG(process, reg_number);
    }
    if (type == DIR_CODE)
        value = get_direct_value(process);
    if (type == IND_CODE)
        value = get_indirect_value(vm, process);
    return value;
}

static void store_result_and_handle_carry(process_t *process, uint32_t result)
{
    int8_t reg_number = *(process->pc++);

    if (reg_number >= 1 && reg_number <= REG_NUMBER) {
        PROC_REG(process, reg_number) = result;
        process->carry = result == 0 ? 1 : 0;
    }
}

void and_op(vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(process->pc++);
    uint32_t first_arg_value = get_value_from_type(\
        vm, process, (args_code >> 6) & 0x3);
    uint32_t second_arg_value = get_value_from_type(\
        vm, process, (args_code >> 4) & 0x3);
    uint32_t result = first_arg_value & second_arg_value;

    if (((args_code >> 2) & 0x3) == REG_CODE)
        store_result_and_handle_carry(process, result);
}

void or_op(vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(process->pc++);
    uint32_t first_arg_value = get_value_from_type(\
        vm, process, (args_code >> 6) & 0x3);
    uint32_t second_arg_value = get_value_from_type(\
        vm, process, (args_code >> 4) & 0x3);
    uint32_t result = first_arg_value | second_arg_value;

    if (((args_code >> 2) & 0x3) == REG_CODE)
        store_result_and_handle_carry(process, result);
}

void xor_op(vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(process->pc++);
    uint32_t first_arg_value = get_value_from_type(\
        vm, process, (args_code >> 6) & 0x3);
    uint32_t second_arg_value = get_value_from_type(\
        vm, process, (args_code >> 4) & 0x3);
    uint32_t result = first_arg_value ^ second_arg_value;

    if (((args_code >> 2) & 0x3) == REG_CODE)
        store_result_and_handle_carry(process, result);
}
