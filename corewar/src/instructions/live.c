/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** live
*/

#include "corewar/corewar.h"
#include "ice/printf.h"

void live(vm_t *vm)
{
    static const char format[] = "The player %d(%s)is alive.\n";
    int32_t number = get_value(vm, DIR_CODE, false, false).direct;
    champion_t *champ;

    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        if (champ->number == number) {
            champ->alive = true;
            vm->live_call_count++;
            ice_printf(format, champ->number, champ->name);
            break;
        }
}
