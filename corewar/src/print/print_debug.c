/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** print_debug
*/

#include "corewar/corewar.h"
#include <stdio.h>

#if defined(DEBUG)
void print_vm(vm_t *vm)
{
        printf(" -- VM -- \n");
        printf("cycle: %ld\n", vm->cycle);
        printf("cycle_to_die: %ld\n", vm->cycle_to_die);
        printf("nb_live: %ld\n", vm->nb_live);
        printf("nb_process: %ld\n", vm->nb_process);
        printf("nb_champ: %ld\n", vm->nb_champ);
        printf("dump: %d\n", vm->dump);
        printf("dump_cycle: %ld\n", vm->dump_cycle);
        printf(" -- END VM -- \n");
        printf(" -- MEMORY -- \n");
        for (size_t i = 0; i < MEM_SIZE; i++) {
            if (i % 32 == 0)
                printf("\n");
            printf("%02x", vm->memory[i]);
        }
        printf("\n");
        printf(" -- END MEMORY -- \n");
}

void print_debug(UNUSED vm_t *vm)
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
        print_vm(vm);
        printf(" -- END DEBUG -- \n");
}
#endif
