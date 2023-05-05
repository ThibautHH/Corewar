/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** create_parse.c
*/

#include <malloc.h>
#include "corewar/asm.h"

parse_t *create_parse(void)
{
    parse_t *parse = malloc(sizeof(parse_t));

    if (!parse)
        return NULL;
    *parse = (parse_t){list_create(), list_create(), 0};
    return (parse->op && parse->label) ? parse : NULL;
}
