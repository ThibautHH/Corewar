/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** parser.c
*/

#include <malloc.h>

#include "corewar/asm.h"

static void destroy_lexer_op(lexer_op_t *op)
{
    for (int i = 0; i < op->op.nbr_args; i++)
        free(op->args[i]);
    free(op);
}

static void destroy_label(label_t *label)
{
    free(label->str);
    free(label);
}

void destroy_lexer(lexer_t *lexer)
{
    list_destroy_node(lexer->op, (void *)destroy_lexer_op);
    list_destroy_node(lexer->label, (void *)destroy_label);
    free(lexer);
}
