/*
** EPITECH PROJECT, 2023
** Corewar/asm
** File description:
** File opening function
*/

#include "asm.h"

bool open_files(asm_t *ctx)
{
    char *output_file = NULL;
    size_t output_file_base_len;

    output_file_base_len = strrtil(FILEN, '.');
    output_file = strndup2(FILEN, output_file_base_len + 5);
    if (!output_file)
        return false;
    ice_strcpy(output_file + output_file_base_len, ".cor");
    F(OUT) = fopen(output_file, "w");
    F(IN) = fopen(FILEN, "r");
    free(output_file);
    return (F(OUT) && F(IN)) ? true : false;
}
