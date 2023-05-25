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

static void next_swap(vm_t *vm, champion_t *i, bool *swapped)
{
    champion_t *next = TAILQ_NEXT(i, entries);

    if (i->number <= next->number)
        return;
    TAILQ_REMOVE(&vm->champ_list, i, entries);
    TAILQ_INSERT_AFTER(&vm->champ_list, next, i, entries);
    *swapped = 1;
}

static void prev_swap(vm_t *vm, champion_t *i, bool *swapped)
{
    champion_t *prev = TAILQ_PREV(i, champions_s, entries);

    if (i->number >= prev->number)
        return;
    TAILQ_REMOVE(&vm->champ_list, i, entries);
    TAILQ_INSERT_BEFORE(prev, i, entries);
    *swapped = 1;
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

void vm_setup(vm_t *vm)
{
    champion_t *champ;

    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        is_champ_number_already_used(champ);
    sort_champions(vm);
    TAILQ_FOREACH(champ, &vm->champ_list, entries) {
        for (size_t i = 0; i < champ->size; i++)
            vm->memory[(champ->load_address + i) % MEM_SIZE] = champ->code[i];
        process_init(vm, champ);
    }
}
