/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** get_smallest_cham_nb
*/

#include "corewar/corewar.h"

int get_smallest_cham_nb(vm_t *vm)
{
    int smallest_nb = 1;
    champion_t *champion = NULL;

    TAILQ_FOREACH(champion, &vm->champ_list, entries) {
        if (champion->number == (size_t)smallest_nb) {
            smallest_nb++;
            champion = TAILQ_FIRST(&vm->champ_list);
        }
    }
    return smallest_nb;
}
