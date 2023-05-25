/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** pre_vm
*/

#include "corewar/corewar.h"

void is_champ_number_already_used(vm_t *vm, int number,
    champion_t *champion_origin);

size_t find_optimal_address(vm_t *vm, size_t size)
{
    size_t default_gap = MEM_SIZE / vm->nb_champ;
    size_t optimal_address = 0;
    size_t gap = 0;
    champion_t *champion = NULL;

    TAILQ_FOREACH(champion, &vm->champ_list, entries) {
        if (champion->load_address != -1)
            continue;
        gap = champion->number * default_gap;
        if (gap > MEM_SIZE)
            gap = gap % MEM_SIZE;
        if (gap + size < MEM_SIZE) {
            optimal_address = gap;
            break;
        }
    }
    return (optimal_address);
}

void pre_vm(vm_t *vm)
{
    champion_t *champion = NULL;

    TAILQ_FOREACH(champion, &vm->champ_list, entries) {
        is_champ_number_already_used(vm, champion->number, champion);
        vm->nb_champ++;
    }

    champion = NULL;
    TAILQ_FOREACH(champion, &vm->champ_list, entries) {
        if (champion->load_address == -1)
            champion->load_address = find_optimal_address(vm, champion->size);
    }

    champion = NULL;
    TAILQ_FOREACH(champion, &vm->champ_list, entries) {
        for (size_t i = 0; i < champion->size; i++)
            vm->memory[champion->load_address + i] = champion->code[i];
    }
}
