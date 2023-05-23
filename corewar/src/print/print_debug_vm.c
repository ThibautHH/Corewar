/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** print_all_champs
*/

#include "corewar/corewar.h"
#include <stdio.h>

#ifdef DEBUG
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
#endif
