/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** destroy_lexer.c
*/

#include <malloc.h>

#include "ice/array.h"
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

void destroy_lexer(char *file, void *head, parse_t *parse)
{
    ice_free_array(head);
    free(file);
    list_destroy_node(L_OP, (void *)destroy_op);
    list_destroy_node(L_LABEL, (void *)destroy_label);
    free(parse);
}
