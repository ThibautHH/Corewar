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
    char **tokens = lexer(&header, file_path);

    free(header);
    return (tokens) ? true : false;
}
