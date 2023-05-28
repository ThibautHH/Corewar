/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** get_next_nb
*/

#include "corewar/corewar.h"

int32_t get_next_nb(vm_t *vm)
{
    int32_t smallest_nb = 1;
    champion_t *champion = NULL;

    TAILQ_FOREACH(champion, &vm->champ_list, entries)
        if (champion->number == smallest_nb) {
            smallest_nb++;
            champion = TAILQ_FIRST(&vm->champ_list);
        }
    return smallest_nb;
}
