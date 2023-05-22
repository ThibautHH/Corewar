/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** print_all_champs
*/

#include "corewar/corewar.h"
#include <stdio.h>

void print_all_champs(UNUSED vm_t vm)
{
    #ifdef DEBUG
        champion_t *champion = NULL;
        TAILQ_FOREACH(champion, &vm.champ_list, entries) {
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
    #endif
}
