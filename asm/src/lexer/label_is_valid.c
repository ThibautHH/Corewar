/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** label_is_valid.c
*/

#include <stdbool.h>

#include "corewar/asm.h"

static bool is_char_valid(char c, const char *valid_char)
{
    for (uint32_t i = 0; valid_char[i]; i++)
        if (valid_char[i] == c)
            return true;
    return false;
}

bool label_is_valid(char *label)
{
    uint32_t i = 0;

    for (; label[i] != ':'; i++) {
        if (!is_char_valid(label[i], LABEL_CHARS))
            return false;
    }
    return is_char_valid(label[++i], SKIPPED_CHARS);
}
