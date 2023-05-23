/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** is_index.c
*/

#include "ice/string.h"
#include "corewar/asm.h"

bool is_index(parser_op_t *op, uint8_t type)
{
    return type == DIR_CODE && (!ice_strcmp(op->mnemonic, "zjmp")
        || !ice_strcmp(op->mnemonic, "ldi")
        || !ice_strcmp(op->mnemonic, "sti")
        || !ice_strcmp(op->mnemonic, "fork"));
}
