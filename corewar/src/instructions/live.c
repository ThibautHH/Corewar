/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** live
*/

#include "corewar/corewar.h"
#include "ice/printf.h"

void live(vm_t *vm, champion_t *champ, process_t *process)
{
    static const char format[] = "The player %d(%s)is alive.\n";
    uint32_t number = 0;

    for (uint8_t i = 0; i < 4; i++)
        number |= *(process->pc++) << (i * 8);
    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        if (champ->number == number) {
            champ->alive = true;
            vm->live_call_count++;
            ice_printf(format, champ->number, champ->name);
            break;
        }
}
