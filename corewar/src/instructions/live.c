/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** live
*/

#include "corewar/corewar.h"
#include "ice/printf.h"
#include <stdio.h>

void live(vm_t *vm, UNUSED champion_t *champ, process_t *process)
{
    uint32_t player_number = get_direct_value(process);
    champion_t *live_champ;

    TAILQ_FOREACH(live_champ, &vm->champ_list, entries) {
        if (live_champ->number == player_number) {
            live_champ->alive = true;
            printf("The player %d(%s) is alive.\n", live_champ->number,
                live_champ->name);
            break;
        }
    }
}
