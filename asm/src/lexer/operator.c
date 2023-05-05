/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** operator.c
*/

#include <malloc.h>

#include "ice/string.h"
#include "ice/memory.h"
#include "corewar/asm.h"

bool create_operator(token_t *token, precoded_op_t **current_op)
{
    *current_op = ice_calloc(1, sizeof(precoded_op_t));
    if (!(*current_op))
        return false;
    for (uint32_t i = 0; i < OP_TAB_SIZE; i++)
        if (!ice_strncmp(P_TOKEN, op_tab[i].mnemonic, P_LEN)) {
            (*current_op)->op = op_tab[i];
            return true;
        }
    free(current_op);
    return false;
}
