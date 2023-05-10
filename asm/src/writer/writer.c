/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** writer.c
*/

#include <stdio.h>

#include "ice/string.h"
#include "corewar/asm.h"

long reverse_int(long value)
{
    long result = 0;

    for (uint16_t offset = 0; offset < 32; offset += 8)
        result = (result << 8) | ((value >> offset) & 0xFF);
    return result;
}

static bool write_header(FILE *file, header_t *header, code_t *code)
{
    header->magic = (int)reverse_int(COREWAR_EXEC_MAGIC);
    header->prog_size = (int)reverse_int(SIZE_BITS);
    return fwrite(header, sizeof(header_t), 1, file) > 0;
}

static bool write_argument(FILE *file, precode_t *precode)
{
    bool len = 1;

    for (uint8_t i = 0; i < MAX_ARGS_NUMBER && len > 0; i++) {
        if (precode->type & (REG_CODE << GET_OFFSET(i))) {
            len = fwrite(&precode->args[i], REG_SIZE, 1, file);
            continue;
        }
        if (precode->type & (IND_CODE << GET_OFFSET(i))) {
            len = fwrite(&precode->args[i], IND_SIZE, 1, file);
            continue;
        }
        if (precode->type & (DIR_CODE << GET_OFFSET(i))) {
            len = fwrite(&precode->args[i], DIR_SIZE, 1, file);
            continue;
        }
    }
    return len > 0;
}

static bool write_instructions(FILE *file, code_t *code)
{
    precode_t *precode;

    for (list_node_t *node = code->precode->head; node; node = node->next) {
        precode = node->value;
        if (!fwrite(&precode->op, OP_SIZE, 1, file)
            || !fwrite(&precode->type, sizeof(uint8_t), 1, file)
            || !write_argument(file, precode))
            return false;
    }
    return true;
}

bool writer(char *filepath, header_t *header,code_t *code)
{
    char filename[ALLOC_SIZE];
    FILE *file;

    filepath = get_filename(filepath);
    if (!filepath)
        return false;
    sprintf(filename, "%s.cor", filepath);
    file = fopen(filename, "w");
    if (!file)
        return false;
    return write_header(file, header, code)
        && write_instructions(file, code)
        && !fclose(file);
}
