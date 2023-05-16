/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** Sting utility functions
*/

#include <sys/types.h>
#include <malloc.h>
#include "ice/string.h"

char *strncpy2(char *dest, const char *src, size_t n)
{
    if (!dest || !src)
        return NULL;
    size_t i = 0;
    size_t src_len = ice_strlen(src);
    size_t cp_end = src_len < n ? src_len : n;
    for (; i < cp_end; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}

char *strndup2(const char *str, size_t n)
{
    size_t length = ice_strlen(str);
    size_t flength = (length < n ? length : n) + 1;
    char *result = malloc(flength * sizeof(char));
    if (!result)
        return NULL;
    strncpy2(result, str, flength);
    return result;
}

size_t strtil(char *str, char c)
{
    register size_t til = 0;

    if (!str)
        return 0;
    while (str[til] && str[til] != c)
        til++;
    return til;
}

ssize_t strrtil(char *str, char c)
{
    register size_t til = ice_strlen(str);

    if (!str)
        return 0;
    for (; til; til--)
        if (str[til] == c)
            return til;
    return (*str == c) ? 0 : -1;
}

int strncmp2(const char *a, const char *b, size_t n)
{
    for (size_t i = 0; a[i] && b[i] && i < n; i++)
        if (a[i] != b[i])
            return (char)(a[i] - b[i]);
    return (char)0;
}
