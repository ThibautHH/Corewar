/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** writer.c
*/

#include <stdio.h>

#include "corewar/asm.h"

/*
 * TODO: error handling on the fwrite
 * TODO: error handling on the fopen
 * TODO: get the filename[.s] from the filepath
 */

static int reverse_int(int value)
{
    int result = 0;

    for (uint16_t offset = 0; offset < 32; offset += 8)
        result = (result << 8) | ((value >> offset) & 0xFF);
    return result;
}

static void write_header(FILE *file, header_t *header, code_t *code)
{
    header->magic = reverse_int(COREWAR_EXEC_MAGIC);
    header->prog_size = reverse_int(SIZE_BITS);
    fwrite(header, sizeof(header_t), 1, file);
}

static void write_argument(FILE *file, precode_t *precode)
{
    for (uint8_t i = 0; i < MAX_ARGS_NUMBER; i++) {
        if (precode->type & (T_REG << GET_OFFSET(i))) {
            fwrite(&precode->args[i], REG_SIZE, 1, file);
            continue;
        }
        if (precode->type & (T_IND << GET_OFFSET(i))) {
            fwrite(&precode->args[i], IND_SIZE, 1, file);
            continue;
        }
        if (precode->type & (T_DIR << GET_OFFSET(i))) {
            fwrite(&precode->args[i], DIR_SIZE, 1, file);
            continue;
        }
    }
}

static void write_instructions(FILE *file, code_t *code)
{
    precode_t *precode;

    for (list_node_t *node = code->precode->head; node; node = node->next) {
        precode = node->value;
        fwrite(&precode->op, OP_SIZE, 1, file);
        fwrite(&precode->type, sizeof(uint8_t), 1, file);
        write_argument(file, precode);
    }
}

void writer(char *filepath, header_t *header,code_t *code)
{
    FILE *file = fopen("txt", "w");

    if (!file)
        return;
    write_header(file, header, code);
    write_instructions(file, code);
    fclose(file);
}
