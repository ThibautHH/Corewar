/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** print_debug
*/

#include "corewar/corewar.h"
#include "corewar/debug_vm.h"
#include <stdio.h>

void print_debug(UNUSED vm_t *vm)
{
    #if defined(DEBUG)
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
        print_vm(vm);
        printf(" -- END DEBUG -- \n");
    #endif
}
