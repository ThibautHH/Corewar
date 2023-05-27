/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** parser.c
*/

#include <malloc.h>

#include "ice/string.h"
#include "ice/memory.h"
#include "corewar/asm.h"

static bool get_label(parser_t *parser, lexer_t *lexer)
{
    label_t *old_label = (lexer->label->head) ?
        lexer->label->head->value : NULL;
    label_t *new_label;

    if (!old_label || old_label->len != parser->size)
        return true;
    parser->size++;
    old_label = list_remove_node(lexer->label, lexer->label->head);
    new_label = ice_calloc(1, sizeof(label_t));
    if (!new_label)
        return false;
    new_label->str = old_label->str;
    new_label->len = parser->size_bits;
    free(old_label);
    return list_add(parser->labels, new_label) && get_label(parser, lexer);
}

static bool set_label(parser_t *parser, search_label_t *search_label)
{
    label_t *label;

    for (list_node_t *node = parser->labels->head; node; node = node->next) {
        label = node->value;
        if (!ice_strcmp(label->str, search_label->name)) {
            *search_label->ptr = label->len - search_label->index;
            return true;
        }
    }
    return false;
}

static parser_op_t *precoder(parser_t *parser, lexer_t *lexer, lexer_op_t *op)
{
    parser_op_t *precode = ice_calloc(1, sizeof(parser_op_t));

    if (!get_label(parser, lexer) || !precode)
        return NULL;
    precode->mnemonic = op->op.mnemonic;
    precode->code = op->op.code;
    parser->tmp_size_bits += 1 + has_coding_byte(op->op.mnemonic);
    for (uint8_t i = 0; i < op->op.nbr_args; i++) {
        if (!add_argument(parser, precode, i, op->args[i]))
            return NULL;
        parser->size++;
    }
    parser->size_bits += parser->tmp_size_bits;
    parser->tmp_size_bits = 0;
    parser->size++;
    return precode;
}

static bool add_last_label(parser_t *parser, lexer_t *lexer)
{
    for (list_node_t *node = lexer->label->head; node;
        node = lexer->label->head) {
        if (!get_label(parser, lexer))
            return false;
        parser->size++;
    }
    return true;
}

parser_t *run_parser(lexer_t *lexer)
{
    parser_t *parser = ice_calloc(1, sizeof(parser_t));

    if (!parser)
        return NULL;
    *parser = (parser_t){lexer->header, list_create(), list_create(),
        list_create(), 0, 0, 0};
    if (!parser->ops || !parser->labels || !parser->search_labels)
        return NULL;
    for (list_node_t *node = lexer->op->head; node; node = node->next)
        if (!list_add(parser->ops, precoder(parser, lexer, node->value)))
            return NULL;
    if (!add_last_label(parser, lexer))
        return NULL;
    for (list_node_t *node = parser->search_labels->head; node;
        node = node->next) {
        if (!set_label(parser, node->value))
            return NULL;
    }
    return parser;
}
