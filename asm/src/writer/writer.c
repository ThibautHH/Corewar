/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** writer.c
*/

#include <stdio.h>

#include "ice/string.h"
#include "corewar/asm.h"

static bool write_argument(FILE *file, parser_op_t *precode)
{
    bool len = 1;

    for (uint8_t i = 0; i < MAX_ARGS_NUMBER && len > 0; i++) {
        if (precode->type & (REG_CODE << GET_OFFSET(i))) {
            len = fwrite(&precode->args[i], REG_SIZE, 1, file);
            continue;
        }
        if (precode->type & (IND_CODE << GET_OFFSET(i))) {
            precode->args[i] = ENDIAN((uint16_t)precode->args[i]);
            len = fwrite(&precode->args[i], IND_SIZE, 1, file);
            continue;
        }
        if (precode->type & (DIR_CODE << GET_OFFSET(i))) {
            precode->args[i] = ENDIAN(precode->args[i]);
            len = fwrite(&precode->args[i], DIR_SIZE, 1, file);
            continue;
        }
    }
    return len > 0;
}

static bool write_instructions(FILE *file, parser_t *parser)
{
    parser_op_t *precode;

    parser->header->magic = ENDIAN(COREWAR_EXEC_MAGIC);
    parser->header->prog_size = ENDIAN(parser->size_bits);
    if (fwrite(parser->header, sizeof(header_t), 1, file) < 0)
        return false;
    for (list_node_t *node = parser->precode->head; node; node = node->next) {
        precode = node->value;
        if (!fwrite(&precode->op, OP_SIZE, 1, file)
            || !fwrite(&precode->type, sizeof(uint8_t), 1, file)
            || !write_argument(file, precode))
            return false;
    }
    return true;
}

bool writer(char *filepath, parser_t *parser)
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
    return write_instructions(file, parser)
        && !fclose(file);
}
