/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** run_vm
*/

#include <stdio.h>
#include "corewar/corewar.h"
#include "ice/memory.h"
#include "ice/printf.h"

void execute_instructon(vm_t *vm, champion_t *champ, process_t *process);
void kill_process(vm_t *vm, champion_t *champ, process_t *process);

static void trim_champ_list(vm_t *vm)
{
    champion_t *champ, *ctmp;
    process_t *process, *ptmp;

    TAILQ_FOREACH_SAFE(champ, &vm->champ_list, entries, ctmp)
        if (!champ->alive)
            TAILQ_FOREACH_SAFE(process, &champ->process_list, entries, ptmp)
                kill_process(vm, champ, process);
}

void run_vm(vm_t *vm)
{
    champion_t *champ, *ctmp;
    process_t *process, *ptmp;

    while (vm->nb_champ > 1) {
        TAILQ_FOREACH_SAFE(champ, &vm->champ_list, entries, ctmp)
            TAILQ_FOREACH_SAFE(process, &champ->process_list, entries, ptmp)
                execute_instructon(vm, champ, process);
        if (++(vm->cycle) == vm->cycle_to_die) {
            trim_champ_list(vm);
            vm->cycle = 0;
        }
        if (vm->live_call_count >= NBR_LIVE) {
            vm->cycle_to_die -= CYCLE_DELTA;
            vm->live_call_count = 0;
        }
    }
    champ = TAILQ_FIRST(&vm->champ_list);
    ice_printf("The player %u(%s)has won.\n", (uint32_t)champ->number, champ->name);
}
