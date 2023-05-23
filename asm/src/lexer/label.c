/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** label_is_valid.c
*/

#include <malloc.h>
#include <stdbool.h>

#include "ice/string.h"
#include "corewar/asm.h"

static bool is_char_valid(char c, const char *valid_char)
{
    for (uint32_t i = 0; valid_char[i]; i++) {
        if (valid_char[i] == c)
            return true;
    }
    return false;
}

static bool label_is_valid(char *label)
{
    uint32_t i = 0;

    for (; label[i] && label[i] != LABEL_CHAR; i++)
        if (!is_char_valid(label[i], LABEL_CHARS))
            return false;
    return label[i] == LABEL_CHAR;
}

bool create_label(lexer_t *lexer, token_t *token)
{
    label_t *label = label_is_valid(token->str) ?
        malloc(sizeof(label_t)) : NULL;

    if (!label)
        return false;
    label->str = ice_strndup(token->str, token->len - 1);
    if (!label->str)
        return false;
    label->len = lexer->count;
    return list_add(lexer->label, label);
}
