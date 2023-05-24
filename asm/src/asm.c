/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** asm.c
*/

#include <malloc.h>

#include "corewar/asm.h"

bool run_asm(char *filepath)
{
    lexer_t *lexer = run_lexer(filepath);
    parser_t *parser = (lexer) ? run_parser(lexer) : NULL;

    if (!parser || !writer(filepath, parser))
        return false;
    destroy_lexer(lexer);
    destroy_parser(parser);
    return true;
}
