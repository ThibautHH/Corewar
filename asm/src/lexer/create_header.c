/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** create_header.c
*/

#include <malloc.h>
#include <stdbool.h>

#include "corewar/asm.h"
#include "ice/string.h"

static ssize_t get_string_len(const char *str)
{
    ssize_t len = 1;

    if (str[0] != STRING_CHAR)
        return -1;
    for (; str[len] && str[len] != STRING_CHAR; len++);
    return (str[len] != STRING_CHAR) ? -1 : len - 1;
}

static bool extract_variable(char *dest, char **token)
{
    ssize_t string_len = get_string_len(*token);

    if (string_len == -1)
        return false;
    ice_strncpy(dest, ++(*token), string_len);
    return !token_skip_chars(*token + string_len + 1)[0];
}

static bool get_variable(char *dest, char ***lines, char *search)
{
    uint32_t token_len = ice_strlen(search);
    char *token;

    for (; *lines[0]; (*lines)++) {
        token = token_skip_chars(*lines[0]);
        if (!token[0])
            continue;
        if (!ice_strncmp(token, search, token_len)) {
            token = token_skip_chars(token + token_len);
            (*lines)++;
            return extract_variable(dest, &token);
        }
    }
    return false;
}

header_t *create_header(char ***lines)
{
    header_t *header = malloc(sizeof(header_t));

    return (header
        && get_variable(header->prog_name, lines, NAME_CMD_STRING)
        && get_variable(header->comment, lines, COMMENT_CMD_STRING))
        ? header : NULL;
}
