/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** label.c
*/

#include "ice/memory.h"
#include "corewar/asm.h"

bool add_search_label(parser_t *parser, parser_op_t *op, char *arg,
    uint32_t index)
{
    search_label_t *search_label = ice_calloc(1, sizeof(search_label_t));

    if (!search_label)
        return false;
    search_label->name = arg + 1;
    search_label->index = parser->size_bits;
    search_label->ptr = &op->args[index];
    return list_add(parser->search_labels, search_label);
}
