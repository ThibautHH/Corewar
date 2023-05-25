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
    vm->cycle_to_die = CYCLE_TO_DIE;
    vm->live_call_count = 0;
    vm->nb_process = 0;
    vm->nb_champ = 0;
    vm->dump = false;
}
