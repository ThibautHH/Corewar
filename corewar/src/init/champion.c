/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** champion
*/

#include <stdio.h>
#include "corewar/corewar.h"
#include "ice/memory.h"
#include "ice/string.h"

static void parse_file(char *filename, champion_t *champion)
{
    FILE *file = fopen(filename, "rb");
    uint32_t magic;

    if (file == NULL)
        exit(84);
    fread(&magic, sizeof(uint32_t), 1, file);
    if (ENDIAN(magic) != COREWAR_EXEC_MAGIC) {
        fwrite("Error: file isn't a corewar binary\n", 1, 36, stderr);
        exit(84);
    }
    fread(champion->name, sizeof(char[PROG_NAME_LENGTH + 1]), 1, file);
    fread(&champion->size, sizeof(uint32_t), 1, file);
    champion->size = ENDIAN(champion->size);
    fread(champion->comment, sizeof(char[COMMENT_LENGTH + 1]), 1, file);
    champion->code = malloc(champion->size);
    if (!champion->code)
        exit(84);
    fread(champion->code, 1, champion->size, file);
    fclose(file);
}

void champion_init(vm_t *vm, uint16_t nb, char *file)
{
    champion_t *champion = malloc(sizeof(champion_t));

    if (!champion)
        exit(84);
    parse_file(file, champion);
    champion->number = nb;
    TAILQ_INIT(&champion->process_list);
    TAILQ_INSERT_TAIL(&vm->champ_list, champion, entries);
    vm->nb_champ++;
}
