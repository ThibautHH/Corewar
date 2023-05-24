/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** token.c
*/

#include "corewar/asm.h"

char *token_skip_chars(char *str)
{
    uint32_t j;

    for (uint32_t i = 0; str[i]; i++) {
        for (j = 0; SKIPPED_CHARS[j] && SKIPPED_CHARS[j] != str[i]; j++);
        if (!SKIPPED_CHARS[j])
            return str + i;
    }
    str[0] = '\0';
    return str;
}

uint32_t token_get_len(const char *str)
{
    uint32_t len = 0;
    uint32_t j;

    for (uint32_t i = 0; str[i]; i++) {
        for (j = 0; SKIPPED_CHARS[j] && SKIPPED_CHARS[j] != str[i]; j++);
        if (SKIPPED_CHARS[j] != '\0')
            break;
        len++;
    }
    return len;
}

void update_token(token_t *token)
{
    token->str += token->len;
    token->str = token_skip_chars(token->str);
    token->len = token_get_len(token->str);
}
