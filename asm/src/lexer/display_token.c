/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** display_token.c
*/

#include "ice/printf.h"
#include "corewar/asm.h"

static void display_label(list_node_t **n_label , precoded_label_t **label,
    uint32_t count)
{
    if (*label && (*label)->index == count) {
        ice_printf("\033[33m[%s]\033[0m\n", (*label)->name);
        *n_label = (*n_label)->next;
        if (*n_label)
            *label = (*n_label)->value;
        else
            *label = NULL;
    }
}

void display_token(parse_t *parse)
{
    uint32_t count = 0;
    precoded_op_t *op;
    list_node_t *n_label = L_LABEL->head;
    precoded_label_t *label = (n_label) ? n_label->value : NULL;

    for (list_node_t *node = L_OP->head; node; node = node->next) {
        op = node->value;
        display_label(&n_label, &label, count);
        ice_printf("\t\033[34m[%s]\033[0m\t", op->op.mnemonic);
        for (uint8_t i = 0; i < op->op.nbr_args; i++) {
            ice_printf("\033[32m[%s]\033[0m\t", op->args[i]);
            count++;
        }
        ice_printf("\n");
        count++;
    }
}
