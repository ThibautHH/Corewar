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
    for (uint32_t i = 0; valid_char[i]; i++)
        if (valid_char[i] == c)
            return true;
    return false;
}

static bool label_is_valid(char *label)
{
    uint32_t i = 0;

    for (; label[i] != ':'; i++) {
        if (!is_char_valid(label[i], LABEL_CHARS))
            return false;
    }
    return is_char_valid(label[++i], SKIPPED_CHARS);
}

bool create_label(parser_t *parser, token_t *token)
{
    precoded_label_t *label = label_is_valid(P_TOKEN) ?
        malloc(sizeof(precoded_label_t)) : NULL;

    if (!label)
        return false;
    label->name = ice_strndup(P_TOKEN, P_LEN - 1);
    if (label->name)
        label->index = T_COUNT;
    return (label->name) ? list_add(L_LABEL, label) : false;
}
