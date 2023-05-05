/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** parser.c
*/

#include <malloc.h>

#include "corewar/asm.h"

static void destroy_op(precoded_op_t *op)
{
    for (int i = 0; i < op->op.nbr_args; i++)
        free(op->args[i]);
    free(op);
}

static void destroy_label(precoded_label_t *label)
{
    free(label->name);
    free(label);
}

void destroy_parser(parser_t *parser)
{
    list_destroy_node(L_OP, (void *)destroy_op);
    list_destroy_node(L_LABEL, (void *)destroy_label);
    free(parser);
}

parser_t *create_parser(void)
{
    parser_t *parser = malloc(sizeof(parser_t));

    if (!parser)
        return NULL;
    *parser = (parser_t){list_create(), list_create(), 0};
    return (parser->op && parser->label) ? parser : NULL;
}
