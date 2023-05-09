/*
** EPITECH PROJECT, 2022
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
        if (size % READ_SIZE != 0)
            break;
        content = realloc(content, sizeof(char) * (size + READ_SIZE + 1));
    }
    fclose(file);
    if (content)
        content[size] = '\0';
    return content;
}

parser_t *lexer(header_t **header, char *filepath)
{
    char *file = get_file(filepath);
    char **lines = (file) ? ice_strsplit(file, "\n") : NULL;
    void *head = (lines) ? &lines[0] : NULL;
    parser_t *parser;

    *header = (head) ? create_header(&lines) : NULL;
    parser = (*header) ? extract(lines) : NULL;
    if (!parser)
        return NULL;
    destroy_lexer(file, head);
    return parser;
}
