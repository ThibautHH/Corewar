/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** extract.c
*/

#include <stdio.h>
#include <malloc.h>

#include "list.h"
#include "ice/string.h"
#include "corewar/asm.h"

static bool as_separator(precoded_op_t *current_op,
    char **token, uint32_t *token_len)
{
    char *last_arg = current_op->args[current_op->arg_count - 1];

    if (current_op->arg_count == 0)
        return true;
    if (last_arg[ice_strlen(last_arg) - 1] == SEPARATOR_CHAR) {
        last_arg[ice_strlen(last_arg) - 1] = '\0';
        printf("\033[32m[%s]\033[0m\t", last_arg);
        return true;
    }
    if (*token[0] == SEPARATOR_CHAR) {
        (*token)++;
        (*token_len)--;
        printf("\033[32m[%s]\033[0m\t", last_arg);
        return true;
    }
    return false;
}

static int handle_token(list_t *op_list, char *token, uint32_t token_len)
{
    static precoded_op_t *current_op = NULL;

    if (current_op) {
        if (!as_separator(current_op, &token, &token_len))
            return printf("\033[31mERROR\033[0m");
        current_op->args[current_op->arg_count++] =
            ice_strndup(token, token_len);
        if (current_op->arg_count == current_op->op.nbr_args) {
            printf("\033[32m[%.*s]\033[0m\n", token_len, token);
            list_add(op_list, current_op);
            current_op = NULL;
        }
        return 0;
    }
    if (token[token_len - 1] == LABEL_CHAR)
        return label_is_valid(token) ?
            printf("\033[33m[%.*s]\033[0m\n", token_len - 1, token) :
            printf("\033[31mERROR\033[0m");
    for (uint32_t i = 0; i < OP_TAB_SIZE; i++)
        if (!ice_strncmp(token, op_tab[i].mnemonic, token_len)) {
            current_op = malloc(sizeof(precoded_op_t));
            current_op->op = op_tab[i];
            return printf("\t\033[34m[%s]\033[0m\t", op_tab[i].mnemonic);
        }
    return 84;
}

void extract(char **lines)
{
    uint32_t token_len;
    list_t *op_list = list_create();

    for (char *token = *lines; token; token = *(lines++)) {
        for (; token[0] && token[0] != COMMENT_CHAR; token += token_len) {
            token = token_skip_chars(token);
            token_len = token_get_len(token);
            if (token[0] == COMMENT_CHAR || token[0] == '\0')
                break;
            handle_token(op_list, token, token_len);
        }
    }
}
