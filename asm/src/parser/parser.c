/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** parser.c
*/

#include "ice/memory.h"
#include "corewar/asm.h"

/*TODO:
 * struct label_s {
 *   char *name;
 *   uint32_t *ptr;
 *   uint32_t index; // index when find
 * } label_t;
 */

precode_t *precoder(code_t *code, precoded_op_t *current_op)
{
    precode_t *precode = ice_calloc(1, sizeof(precode_t));

    SIZE++;
    if (!precode)
        return NULL;
    for (uint8_t i = 0; i < OP.nbr_args; i++) {
        precode->op = OP.code;
        if (!add_argument(code, precode, i, ARGS[i]))
            return NULL;
    }
    return precode;
}

code_t *parse(parser_t *parser)
{
    code_t *code = ice_calloc(1, sizeof(code_t));

    PRECODE = (code) ? list_create() : NULL;
    if (!PRECODE)
        return NULL;
    for (list_node_t *node = L_OP->head; node; node = node->next)
        if (!list_add(PRECODE, precoder(code, node->value)))
            return NULL;
    return code;
}
