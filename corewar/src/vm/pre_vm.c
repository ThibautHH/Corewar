/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** pre-vm
*/

#include "corewar/corewar.h"
#include "ice/memory.h"

void is_champ_number_already_used(champion_t *champ);
void process_init(vm_t *vm, champion_t *champ);

void pre_vm(vm_t *vm)
{
    champion_t *champ = NULL;

    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        is_champ_number_already_used(champ);
    TAILQ_FOREACH(champ, &vm->champ_list, entries) {
        for (size_t i = 0; i < champ->size; i++)
            vm->memory[(champ->load_address + i) % MEM_SIZE] = champ->code[i];
        process_init(vm, champ);
    }
}
