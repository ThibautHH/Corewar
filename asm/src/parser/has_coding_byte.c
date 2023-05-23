/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** has_coding_byte.c
*/

#include "ice/string.h"
#include "corewar/asm.h"

bool has_coding_byte(char *mnemonic)
{
    return !(!ice_strcmp(mnemonic, "live")
        || !ice_strcmp(mnemonic, "zjmp")
        || !ice_strcmp(mnemonic, "fork")
        || !ice_strcmp(mnemonic, "lfork"));
}
