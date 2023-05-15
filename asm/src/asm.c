/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** asm.c
*/

#include <malloc.h>

#include "corewar/asm.h"

/*
 * TODO: Proper naming
 * TODO: Free all the memory
 * TODO: Error handling on the return value
 * TODO: BONUS: See error and the line were occurred
 */

bool asm_f(char *filepath)
{
    header_t *header;
    parser_t *parser = lexer(&header, filepath);
    code_t *code = (parser) ? parse(parser) : NULL;

    if (!code || !writer(filepath, header, code))
        return false;
    destroy_parser(parser);
    free(header);
    return true;
}
