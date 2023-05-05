/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** asm.c
*/

#include <malloc.h>

#include "corewar/asm.h"

bool asm_f(char *file_path)
{
    header_t *header;
    parser_t *parser = lexer(&header, file_path);

    free(header);
    destroy_parser(parser);
    return (parser) ? true : false;
}
