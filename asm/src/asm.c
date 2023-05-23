/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** asm.c
*/

#include <malloc.h>

#include "corewar/asm.h"

/*
 * TODO: Error handling on the return value
 */

bool asm_f(char *filepath)
{
    lexer_t *lexer = lexer_f(filepath);
    parser_t *parser = (lexer) ? parser_f(lexer) : NULL;

    if (!parser || !writer(filepath, parser))
        return false;
    destroy_lexer(lexer);
    destroy_parser(parser);
    return true;
}
