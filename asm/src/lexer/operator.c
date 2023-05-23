/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** operator.c
*/

#include <malloc.h>

#include "ice/string.h"
#include "ice/memory.h"
#include "corewar/asm.h"

bool create_operator(token_t *token, lexer_op_t **op)
{
    *op = ice_calloc(1, sizeof(lexer_op_t));
    if (!(*op))
        return false;
    for (uint32_t i = 0; i < OP_TAB_SIZE; i++)
        if (!ice_strncmp(token->str, op_tab[i].mnemonic, token->len)) {
            (*op)->op = op_tab[i];
            return true;
        }
    free(*op);
    return false;
}
