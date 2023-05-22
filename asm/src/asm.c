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
    header_t *header;
    lexer_t *parser = lexer_f(&header, filepath);
    parser_t *code = (parser) ? parser_f(parser) : NULL;

    if (!code || !writer(filepath, header, code))
        return false;
    destroy_lexer(parser);
    free(header);
    return true;
}
