/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** extract.c
*/

#include "ice/string.h"
#include "corewar/asm.h"

static bool as_separator(lexer_op_t *op, token_t *token)
{
    if (op->arg_count != 0) {
        if (token->str[0] != SEPARATOR_CHAR)
            return false;
        token->str++;
        token->len--;
    }
    for (uint32_t i = 0; token->str[i]; i++) {
        if (token->str[i] == SEPARATOR_CHAR) {
            token->len = i;
            return true;
        }
    }
    return true;
}

static bool handle_token(lexer_t *lexer, token_t *token)
{
    static lexer_op_t *op = NULL;

    if (op) {
        if (!as_separator(op, token))
            return false;
        op->args[op->arg_count] =
            ice_strndup(token->str, token->len);
        if (!op->args[op->arg_count++])
            return false;
        if (op->arg_count == op->op.nbr_args) {
            list_add(lexer->op, op);
            op = NULL;
        }
        return true;
    }
    return (token->str[token->len - 1] == LABEL_CHAR) ?
        create_label(lexer, token) : create_operator(token, &op);
}

static bool read_line(lexer_t *lexer, token_t *token)
{
    for (; token->str[0] && token->str[0] != COMMENT_CHAR;) {
        update_token(token);
        if (token->str[0] == COMMENT_CHAR || token->str[0] == '\0')
            return true;
        if (!handle_token(lexer, token))
            return false;
        lexer->count++;
    }
    return true;
}

bool extract(lexer_t *lexer, char **lines)
{
    token_t tmp = (token_t){*lines, 0};
    token_t *token = &tmp;

    if (!lexer)
        return false;
    if (token->str)
        token->str = *(lines++);
    else
        return false;
    for (; token->str; token->str = *(lines++)) {
        if (!read_line(lexer, token))
            return false;
        token->len = 0;
    }
    return true;
}
