/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** vm
*/

#include "corewar/corewar.h"
#include "ice/memory.h"

void vm_init(vm_t *vm)
{
    TAILQ_INIT(&vm->champ_list);
    vm->cycle = 0;
    vm->cycle_to_die = (vm->dump_cycle) ? 1 : CYCLE_TO_DIE;
    vm->nb_live = 0;
    vm->nb_process = 0;
    vm->nb_champ = 0;
    vm->dump = false;
}
