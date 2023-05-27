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

static bool is_skipped_char(char c)
{
    for (uint32_t i = 0; SKIPPED_CHARS[i]; i++)
        if (c == SKIPPED_CHARS[i])
            return true;
    return false;
}

static bool clean_line(token_t *token)
{
    uint32_t j = token->len + 2;
    uint32_t i = token->len + 2;

    if (!is_skipped_char(token->str[token->len]))
        return false;
    for (; token->str[i]; i++) {
        if (is_skipped_char(token->str[i]))
            continue;
        token->str[j++] = token->str[i];
    }
    token->str[j] = '\0';
    return true;
}

bool create_operator(token_t *token, lexer_op_t **op)
{
    *op = ice_calloc(1, sizeof(lexer_op_t));
    if (!(*op))
        return false;
    for (uint32_t i = 0; i < OP_TAB_SIZE; i++)
        if (!ice_strncmp(token->str, op_tab[i].mnemonic, token->len)) {
            (*op)->op = op_tab[i];
            return clean_line(token);
        }
    free(*op);
    return false;
}
