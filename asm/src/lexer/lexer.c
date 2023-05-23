/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** lexer.c
*/

#include <stdio.h>
#include <malloc.h>

#include "ice/array.h"
#include "ice/string.h"
#include "corewar/asm.h"

/*
 * TODO: Rewrite this function
 */

static char *get_file(char *filepath)
{
    FILE *file = fopen(filepath, "r");
    char *content = malloc(sizeof(char) * (READ_SIZE + 1));
    unsigned int size = 0;

    if (!file || !content)
        return NULL;
    while (content) {
        size += fread(content + size, sizeof(char), READ_SIZE, file);
        if (size % READ_SIZE != 0 || size == 0)
            break;
        content = realloc(content, sizeof(char) * (size + READ_SIZE + 1));
    }
    fclose(file);
    if (!content)
        return NULL;
    content[size] = '\0';
    return (content[0]) ? content : NULL;
}

lexer_t *create_lexer(char ***lines)
{
    lexer_t *lexer = malloc(sizeof(lexer_t));

    if (!lexer)
        return NULL;
    *lexer = (lexer_t){create_header(lines), list_create(), list_create(), 0};
    return (lexer->header && lexer->op && lexer->label) ? lexer : NULL;
}

lexer_t *lexer_f(char *filepath)
{
    char *file = get_file(filepath);
    char **lines = (file) ? ice_strsplit(file, "\n") : NULL;
    void *head = (lines) ? &lines[0] : NULL;
    lexer_t *lexer = (lines) ? create_lexer(&lines) : NULL;

    if (!lexer || !extract(lexer, lines))
        return NULL;
    ice_free_array(head);
    free(file);
    return lexer;
}
