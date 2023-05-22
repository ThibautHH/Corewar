/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** extract.c
*/

#include <malloc.h>

#include "ice/string.h"
#include "corewar/asm.h"

lexer_t *create_lexer(void)
{
    lexer_t *lexer = malloc(sizeof(lexer_t));

    if (!lexer)
        return NULL;
    *lexer = (lexer_t){list_create(), list_create(), 0};
    return (lexer->op && lexer->label) ? lexer : NULL;
}

static bool as_separator(lexer_op_t *op, token_t *token)
{
    char *last_arg = op->args[op->arg_count - 1];

    if (op->arg_count == 0)
        return true;
    if (last_arg[ice_strlen(last_arg) - 1] == SEPARATOR_CHAR) {
        last_arg[ice_strlen(last_arg) - 1] = '\0';
        return true;
    }
    if (token->str[0] == SEPARATOR_CHAR) {
        (token->str)++;
        (token->len)--;
        return true;
    }
    return false;
}

static bool handle_token(lexer_t *lexer, token_t *token)
{
    static lexer_op_t *op = NULL;

    if (op) {
        if (!as_separator(op, token))
            return false;
        op->args[op->arg_count++] =
            ice_strndup(token->str, token->len);
        if (op->arg_count == op->op.nbr_args) {
            list_add(lexer->op, op);
            op = NULL;
        }
        return true;
    }
    return (token->str[token->len - 1] == LABEL_CHAR) ?
        create_label(lexer, token) : create_operator(token, &op);
}

lexer_t *extract(char **lines)
{
    lexer_t *parser = create_lexer();
    token_t tmp = (token_t){*lines, 0};
    token_t *token = &tmp;

    if (!parser)
        return NULL;
    for (; token->str; token->str = *(lines++)) {
        for (; token->str[0] && token->str[0] != COMMENT_CHAR;) {
            update_token(token);
            if (token->str[0] == COMMENT_CHAR || token->str[0] == '\0')
                break;
            handle_token(parser, token);
            parser->count++;
        }
    }
    return parser;
}
