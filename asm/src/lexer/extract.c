/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** extract.c
*/

#include "ice/string.h"
#include "corewar/asm.h"

static bool as_separator(precoded_op_t *current_op, token_t *token)
{
    char *last_arg = ARGS[ARG_COUNT - 1];

    if (ARG_COUNT == 0)
        return true;
    if (last_arg[ice_strlen(last_arg) - 1] == SEPARATOR_CHAR) {
        last_arg[ice_strlen(last_arg) - 1] = '\0';
        return true;
    }
    if (P_TOKEN[0] == SEPARATOR_CHAR) {
        (P_TOKEN)++;
        (P_LEN)--;
        return true;
    }
    return false;
}

static bool handle_token(parser_t *parser, token_t *token)
{
    static precoded_op_t *current_op = NULL;

    if (current_op) {
        if (!as_separator(current_op, token))
            return false;
        ARGS[ARG_COUNT++] =
            ice_strndup(P_TOKEN, P_LEN);
        if (ARG_COUNT == OP.nbr_args) {
            list_add(L_OP, current_op);
            current_op = NULL;
        }
        return true;
    }
    return (P_TOKEN[P_LEN - 1] == LABEL_CHAR) ? create_label(parser, token) :
        create_operator(token, &current_op);
}

parser_t *extract(char **lines)
{
    parser_t *parser = create_parser();

    if (!parser)
        return NULL;
    for (token_t token = (token_t){*lines, 0}; TOKEN; TOKEN = *(lines++)) {
        for (; TOKEN[0] && TOKEN[0] != COMMENT_CHAR; TOKEN += LEN) {
            TOKEN = token_skip_chars(TOKEN);
            LEN = token_get_len(TOKEN);
            if (TOKEN[0] == COMMENT_CHAR || TOKEN[0] == '\0')
                break;
            handle_token(parser, &token);
            T_COUNT++;
        }
    }
    return parser;
}
