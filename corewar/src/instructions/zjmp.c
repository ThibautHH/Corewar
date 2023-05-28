/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** zjmp
*/

#include "corewar/corewar.h"

void zjmp(vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint8_t args_code = *(NEXT_BYTE);
    int32_t index = 0;

    if (process->carry == 1) {
        if ((args_code >> 6) == DIR_CODE) {
            index = get_direct_value(vm, process);
        }
        process->pc = vm->memory + (\
            (process->pc - vm->memory + (index % IDX_MOD)) % MEM_SIZE);
    }
}
