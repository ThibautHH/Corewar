/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** pre-vm
*/

#include "corewar/corewar.h"
#include "ice/memory.h"

void is_champ_number_already_used(champion_t *champ);

void pre_vm(vm_t *vm)
{
    champion_t *champ = NULL;

    TAILQ_FOREACH(champ, &vm->champ_list, entries)
        is_champ_number_already_used(champ);
    TAILQ_FOREACH(champ, &vm->champ_list, entries) {
        for (size_t i = 0; i < champ->size; i++)
            vm->memory[(champ->load_address + i) % MEM_SIZE] =
                champ->code[i];
    }
    TAILQ_FOREACH(champ, &vm->champ_list, entries) {
        process_t *process = malloc(sizeof(process_t));
        if (process == NULL) exit(84);
        process->carry = 0;
        process->pc = champ->load_address;
        ice_memset(process->reg, 0, sizeof(process->reg));
        process->reg[0].reg[0] = champ->number;
        TAILQ_INSERT_TAIL(&champ->process_list, process, entries);
        vm->nb_process++;
    }
}
