/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** print_debug
*/

#include "corewar/corewar.h"
#include <stdio.h>
#include <unistd.h>

#if defined(DEBUG)

void instructions_debug(champion_t *champ, op_t op)
{
    printf("\033[0;32mDEBUG\033[0m : Player %d(%s) is executing %s\n",
        champ->number, champ->name, op.mnemonic);
    usleep(500000);
}

void print_vm(vm_t *vm)
{
        printf("\033[0;32mVM \033[0m\n");
        printf("cycle: %ld\n", vm->cycle);
        printf("cycle_to_die: %ld\n", vm->cycle_to_die);
        printf("live_call_count: %ld\n", vm->live_call_count);
        printf("nb_process: %ld\n", vm->nb_process);
        printf("nb_champ: %ld\n", vm->nb_champ);
        printf("dump: %d\n", vm->dump);
        printf("dump_cycle: %ld\n", vm->dump_cycle);
        printf("\033[0;32mEND VM \033[0m\n");
        printf("\033[0;32mMEMORY \033[0m\n");
        for (size_t i = 0; i < MEM_SIZE; i++) {
            if (i % 32 == 0)
                printf("\n");
            printf("%02x", vm->memory[i]);
        }
        printf("\n");
        printf("\033[0;32mEND MEMORY \033[0m\n");
}

void print_debug(vm_t *vm)
{
        printf("\033[0;32mDEBUG \033[0m\n");
        printf("\033[0;32mCHAMPIONS \033[0m\n");
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
            printf("champion number: %hu\n", champion->number);
            printf("\n");
        }
        printf("\033[0;32mEND CHAMPIONS \033[0m\n");
        print_vm(vm);
        printf("\033[0;32mEND DEBUG \033[0m\n");
        printf("\n");
}

void store_vm_memory(vm_t *vm, char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
        return;
    for (size_t i = 0; i < MEM_SIZE; i++) {
        if (i % 32 == 0)
            fprintf(file, "\n");
        fprintf(file, "%02x", vm->memory[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

#endif
