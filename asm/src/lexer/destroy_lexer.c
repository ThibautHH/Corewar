/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** destroy_lexer.c
*/

#include <malloc.h>

#include "ice/array.h"

void destroy_lexer(char *file, void *head)
{
    ice_free_array(head);
    free(file);
}
