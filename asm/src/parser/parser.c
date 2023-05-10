/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** parser.c
*/

#include <malloc.h>

#include "ice/memory.h"
#include "corewar/asm.h"
#include "ice/string.h"

/*TODO:
 * struct label_s {
 *   char *name;
 *   uint32_t *ptr;
 *   uint32_t index; // index when find
 * } label_t;
 */

static bool get_label(code_t *code, parser_t *parser)
{
    precoded_label_t *old_label = (parser->label->head) ?
        parser->label->head->value : NULL;
    label_t *new_label;

    if (!old_label || old_label->index != SIZE)
        return true;
    old_label = list_remove_node(parser->label, parser->label->head);
    new_label = ice_calloc(1, sizeof(label_t));
    if (!new_label)
        return false;
    new_label->name = old_label->name;
    new_label->index = SIZE_BITS;
    free(old_label);
    return list_add(code->labels, new_label);
}

static void set_label(code_t *code, search_label_t *search_label)
{
    label_t *label;

    for (list_node_t *node = LABELS->head; node; node = node->next) {
        label = node->value;
        if (!ice_strcmp(label->name, search_label->name)) {
            *search_label->ptr = label->index - search_label->index;
            break;
        }
    }
}

static precode_t *precoder(code_t *code, parser_t *parser,
    precoded_op_t *current_op)
{
    precode_t *precode = ice_calloc(1, sizeof(precode_t));

    if (!get_label(code, parser) || !precode)
        return NULL;
    for (uint8_t i = 0; i < OP.nbr_args; i++) {
        precode->op = OP.code;
        if (!add_argument(code, precode, i, ARGS[i]))
            return NULL;
        SIZE++;
    }
    SIZE++;
    return precode;
}

code_t *parse(parser_t *parser)
{
    code_t *code = ice_calloc(1, sizeof(code_t));

    PRECODE = (code) ? list_create() : NULL;
    LABELS = (PRECODE) ? list_create() : NULL;
    SEARCH_LABELS = (LABELS) ? list_create() : NULL;
    if (!SEARCH_LABELS)
        return NULL;
    for (list_node_t *node = L_OP->head; node; node = node->next)
        if (!list_add(PRECODE, precoder(code, parser, node->value)))
            return NULL;
    for (list_node_t *node = SEARCH_LABELS->head; node; node = node->next)
        set_label(code, node->value);
    return code;
}
