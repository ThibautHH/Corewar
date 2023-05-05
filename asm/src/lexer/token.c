/*
** EPITECH PROJECT, 2022
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
        if (SKIPPED_CHARS[j] == '\0')
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
