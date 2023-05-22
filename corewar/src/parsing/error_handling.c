/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** error_handling
*/

#include <stdio.h>
#include "ice/string.h"
#include "corewar/corewar.h"
const char *number_used_several_times = "Error: number used several times\n";

void is_champ_number_already_used(vm_t *vm, int number,
    champion_t *champion_origin)
{
    champion_t *champion = NULL;

    TAILQ_FOREACH(champion, &vm->champ_list, entries) {
        if (champion == champion_origin)
            continue;
        if (champion->number == (size_t)number) {
            fwrite(number_used_several_times, 1,
                ice_strlen(number_used_several_times), stderr);
            exit(84);
        }
    }
}
