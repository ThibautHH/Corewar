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
#include "ice/output.h"

void execute_instructon(vm_t *vm, champion_t *champ, process_t *process);
void kill_process(vm_t *vm, champion_t *champ, process_t *process);

static const char win_fmt[] = "The player %u(%s)has won.\n";

static void dump_memory(vm_t *vm)
{
    static char line[(32 * 3) + 1] = {0};
    register char *head = line;

    for (uint8_t *p = vm->memory; p < vm->memory + MEM_SIZE;) {
        while (head < line + (32 * 3))
            head += ice_sprintf(head, " %02X", *(p++));
        head = line;
        ice_printf("%-4X :%s\n", (uint32_t)(p - vm->memory) - 32, line);
    }
}

static void trim_champ_list(vm_t *vm)
{
    champion_t *champ, *ctmp;
    process_t *process, *ptmp;

    TAILQ_FOREACH_SAFE(champ, &vm->champ_list, entries, ctmp)
        if (!champ->alive)
            TAILQ_FOREACH_SAFE(process, &champ->process_list, entries, ptmp)
                kill_process(vm, champ, process);
    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        champ->alive = false;
}

static void end_of_game(vm_t *vm)
{
    if (vm->dump && vm->cycle == vm->dump_cycle)
        dump_memory(vm);
    if (vm->nb_champ == 1)
        ice_printf(win_fmt, (uint32_t)FIRST_CHAMP->number, FIRST_CHAMP->name);
    else if (vm->nb_champ == 0)
        ice_puts("The last players died at the same time, it's a tie.\n");
}

void run_vm(vm_t *vm)
{
    champion_t *champ, *ctmp;
    process_t *process, *ptmp;

    while (vm->nb_champ > 1 && (!vm->dump || vm->cycle != vm->dump_cycle)) {
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
    end_of_game(vm);
}
