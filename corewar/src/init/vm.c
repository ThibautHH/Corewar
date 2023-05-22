/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** vm
*/

#include "corewar/corewar.h"
#include "ice/memory.h"

void vm_init(vm_t *vm, size_t cycle_to_die)
{
    ice_memset(vm->memory, 0, sizeof(vm->memory));
    LIST_INIT(&vm->champ_list);
    vm->cycle = 0;
    vm->cycle_to_die = cycle_to_die;
    vm->nb_live = 0;
    vm->nb_process = 0;
    vm->nb_champ = 0;
    vm->dump = false;
    vm->dump_cycle = 0;
}
