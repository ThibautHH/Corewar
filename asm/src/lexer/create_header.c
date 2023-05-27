/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** create_header.c
*/

#include "ice/memory.h"
#include "ice/string.h"
#include "corewar/asm.h"

static ssize_t get_string_len(const char *str)
{
    ssize_t len = 1;

    if (str[0] != STRING_CHAR)
        return -1;
    for (; str[len] && str[len] != STRING_CHAR; len++);
    return (str[len] != STRING_CHAR) ? -1 : len - 1;
}

static bool extract_variable(char *dest, char **token, uint32_t max_len)
{
    ssize_t string_len = get_string_len(*token);

    if (string_len == -1 || string_len > max_len)
        return false;
    ice_strncpy(dest, ++(*token), string_len);
    return !token_skip_chars(*token + string_len + 1)[0];
}

static bool as_comment(char **lines)
{
    for (uint32_t i = 0; lines[i]; i++)
        if (ice_strstr(lines[i], COMMENT_CMD_STRING))
            return true;
    return false;
}

static bool get_variable(char *dest, char ***lines, char *search,
    uint32_t max_len)
{
    uint32_t token_len = ice_strlen(search);
    char *token;

    if (max_len == COMMENT_LENGTH && !as_comment(*lines))
        return true;
    for (; *lines[0]; (*lines)++) {
        token = token_skip_chars(*lines[0]);
        if (!token[0])
            continue;
        if (!ice_strncmp(token, search, token_len)) {
            token = token_skip_chars(token + token_len);
            (*lines)++;
            return extract_variable(dest, &token, max_len);
        }
    }
    return false;
}

header_t *create_header(char ***lines)
{
    header_t *header = ice_calloc(1, sizeof(header_t));

    return (header
        && get_variable(header->prog_name, lines, NAME_CMD_STRING,
        PROG_NAME_LENGTH)
        && get_variable(header->comment, lines, COMMENT_CMD_STRING,
        COMMENT_LENGTH))
        ? header : NULL;
}
