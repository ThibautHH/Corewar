/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** destroy.c
*/

#include <malloc.h>

#include "corewar/asm.h"

static void destroy_label(label_t *label)
{
    free(label->str);
    free(label);
}

void destroy_parser(parser_t *parser)
{
    list_destroy_node(parser->ops, free);
    list_destroy_node(parser->labels, (void *)destroy_label);
    list_destroy_node(parser->search_labels, free);
    free(parser->header);
    free(parser);
}
