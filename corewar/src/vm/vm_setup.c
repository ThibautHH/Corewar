/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** vm_setup
*/

#include <stdio.h>
#include "corewar/corewar.h"
#include "ice/memory.h"

void process_init(vm_t *vm, champion_t *champ);

static const char used_number[] = "Error: number used several times\n";

static void is_champ_number_already_used(champion_t *champ)
{
    for (champion_t *other = TAILQ_NEXT(champ, entries); (other);
        (other = TAILQ_NEXT(other, entries)))
        if (other->number == champ->number) {
            fwrite(used_number, sizeof(used_number), 1, stderr);
            exit(84);
        }
}

static void sort_champions(vm_t *vm)
{
    bool swapped = 1;
    for (champion_t *first = FIRST_CHAMP, *last = LAST_CHAMP;
        swapped; first = TAILQ_NEXT(first, entries)) {
        swapped = 0;
        for (champion_t *i = first; i != last; i = TAILQ_NEXT(i, entries))
            next_swap(vm, i, &swapped);
        if (!swapped)
            break;
        last = TAILQ_PREV(last, champions_s, entries);
        swapped = 0;
        for (champion_t *i = last; i != first; i = TAILQ_PREV(i, champions_s,
            entries))
            prev_swap(vm, i, &swapped);
    }
}

static void set_load_address(vm_t *vm)
{
    champion_t *champ;
    uint16_t size_sum = 0, gap_size;

    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        size_sum += champ->size;
    if (size_sum > MEM_SIZE) {
        fwrite("Error: champions are too big\n", sizeof(char[30]), 1, stderr);
        exit(84);
    }
    gap_size = (MEM_SIZE - size_sum) / vm->nb_champ;
    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        if (champ->load_address == -1)
            champ->load_address = TAILQ_PREV(champ, champions_s, entries) ?
                TAILQ_PREV(champ, champions_s, entries)->load_address +
                TAILQ_PREV(champ, champions_s, entries)->size + gap_size : 0;
}

void vm_setup(vm_t *vm)
{
    champion_t *champ;

    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        is_champ_number_already_used(champ);
    sort_champions(vm);
    set_load_address(vm);
    TAILQ_FOREACH(champ, &vm->champ_list, entries) {
        for (size_t i = 0; i < champ->size; i++)
            vm->memory[(champ->load_address + i) % MEM_SIZE] = champ->code[i];
        process_init(vm, champ);
    }
}
