/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** asm.c
*/

#include <malloc.h>

#include "corewar/asm.h"

/*
 * TODO: Free all the memory
 * TODO: Error handling on the return value
 * TODO: BONUS: See error and the line were occurred
 */

bool asm_f(char *filepath)
{
    lexer_t *lexer = lexer_f(filepath);
    parser_t *parser = (lexer) ? parser_f(lexer) : NULL;

    if (!parser || !writer(filepath, parser))
        return false;
    destroy_lexer(lexer);
    return true;
}
