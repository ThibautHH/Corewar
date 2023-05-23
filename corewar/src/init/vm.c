/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** vm
*/

#include "corewar/corewar.h"
#include "ice/memory.h"

static int count_champs(vm_t *vm)
{
    int count = 0;
    champion_t *champ = NULL;

    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        count++;
    return count;
}

void vm_init(vm_t *vm)
{
    ice_memset(vm->memory, 0, sizeof(vm->memory));
    TAILQ_INIT(&vm->champ_list);
    vm->cycle = 0;
    vm->cycle_to_die = (vm->dump_cycle == 0) ? CYCLE_TO_DIE : 1;
    vm->nb_live = 0;
    vm->nb_process = 0;
    vm->nb_champ = count_champs(vm);
    vm->dump = false;
}
