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

static void destroy_lexer(char *file, void *head)
{
    ice_free_array(head);
    free(file);
}

char **lexer(header_t **header, char *filepath)
{
    char *file = get_file(filepath);
    char **lines = (file) ? ice_strsplit(file, "\n") : NULL;
    void *head = (lines) ? &lines[0] : NULL;

    *header = (head) ? create_header(&lines) : NULL;
    if (!(*header))
        return NULL;
    extract(lines);
    destroy_lexer(file, head);
    return NULL;
}
