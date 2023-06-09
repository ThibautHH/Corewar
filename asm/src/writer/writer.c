/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** writer.c
*/

#include <stdio.h>

#include "ice/string.h"
#include "ice/printf.h"
#include "corewar/asm.h"

static bool write_argument(FILE *file, parser_op_t *op)
{
    bool len = 1;
    uint8_t type;

    for (uint8_t i = 0; i < MAX_ARGS_NUMBER - 1 && len > 0; i++) {
        type = ((op->type << i * 2) & 0b11000000) >> 6;
        if (type == REG_CODE)
            len = fwrite(&op->args[i], 1, 1, file);
        if (type == IND_CODE || is_index(op, type)) {
            op->args[i] = ENDIAN((uint16_t)op->args[i]);
            len = fwrite(&op->args[i], IND_SIZE, 1, file);
            continue;
        }
        if (type == DIR_CODE) {
            op->args[i] = ENDIAN(op->args[i]);
            len = fwrite(&op->args[i], DIR_SIZE, 1, file);
        }
    }
    return len > 0;
}

static bool write_type(FILE *file, parser_op_t *op)
{
    return has_coding_byte(op->mnemonic) ?
        fwrite(&op->type, sizeof(uint8_t), 1, file) : true;
}

static bool write_instructions(FILE *file, parser_t *parser)
{
    parser_op_t *op;

    parser->header->magic = ENDIAN(COREWAR_EXEC_MAGIC);
    parser->header->prog_size = ENDIAN(parser->size_bits);
    if (!fwrite(parser->header, sizeof(header_t), 1, file))
        return false;
    for (list_node_t *node = parser->ops->head; node; node = node->next) {
        op = node->value;
        if (!fwrite(&op->code, OP_SIZE, 1, file)
            || !write_type(file, op) || !write_argument(file, op))
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
    ice_sprintf(filename, "%s.cor", filepath);
    file = fopen(filename, "w");
    if (!file)
        return false;
    return write_instructions(file, parser) && !fclose(file);
}
