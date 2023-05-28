/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** aff
*/

#include <stdio.h>
#include "corewar/corewar.h"

void aff(UNUSED vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(process->pc++);
    uint32_t first_arg_value = 0;

    if (((args_code >> 4) & 0x3) == REG_CODE) {
        first_arg_value = get_register_value(process);
        printf("%c", first_arg_value % 256);
    }
}
