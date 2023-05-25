/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** print_all_champs
*/

#include "corewar/corewar.h"
#include <stdio.h>

#if defined(DEBUG)

void print_memory(vm_t *vm)
{
    printf(" -- MEMORY -- \n");
    for (size_t i = 0; i < MEM_SIZE; i++) {
        if (i % 32 == 0)
            printf("\n");
        printf("%02x ", vm->memory[i]);
    }
    printf("\n");
    printf(" -- END MEMORY -- \n");
}

void print_vm(vm_t *vm)
{
    printf(" -- VM -- \n");
    printf("cycle_to_die: %ld\n", vm->cycle_to_die);
    printf(" -- END VM -- \n");
}

void print_debug(vm_t *vm)
{
    printf(" -- DEBUG -- \n");
    printf(" -- CHAMPIONS -- \n");
    champion_t *champion = NULL;
    TAILQ_FOREACH(champion, &vm->champ_list, entries) {
        printf("champion name: %s\n", champion->name);
        printf("champion comment: %s\n", champion->comment);
        printf("champion size: %d\n", champion->size);
        printf("champion code: ");
        for (size_t i = 0; i < champion->size; i++)
            printf("%02x", champion->code[i]);
        printf("\n");
        printf("champion load address: %ld\n", champion->load_address);
        printf("champion number: %ld\n", champion->number);
        printf("\n");
    }
    printf(" -- END CHAMPIONS -- \n");
    print_memory(vm);
    print_vm(vm);
    printf(" -- END DEBUG -- \n");
}

#endif
