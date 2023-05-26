/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** live
*/

#include "corewar/corewar.h"

void live(vm_t *vm, champion_t *champ, process_t *process)
{
    uint32_t number = 0;

    for (uint8_t i = 0; i < 4; i++)
        number |= *(process->pc++) << (i * 8);
    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        if (champ->number == number) {
            champ->alive = true;
            vm->live_call_count++;
            break;
        }
}
