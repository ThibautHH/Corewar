/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** add_argument.c
*/

#include "ice/int.h"
#include "corewar/asm.h"

static bool add_reg(parser_t *parser, parser_op_t *op, uint8_t index, char *arg)
{
    char *endptr;
    int value = (int)ice_strtol(arg + 1, &endptr);

    if (*endptr || value <= 0 || value > REG_NUMBER)
        return false;
    op->type |= REG_CODE << GET_OFFSET(index);
    parser->tmp_size_bits += 1;
    op->args[index] = value;
    return true;
}

static bool add_dir(parser_t *parser, parser_op_t *op, uint8_t index, char *arg)
{
    char *endptr;
    int value;

    op->type |= DIR_CODE << GET_OFFSET(index);
    parser->tmp_size_bits += is_index(op, DIR_CODE) ? IND_SIZE : DIR_SIZE;
    if (arg[1] == LABEL_CHAR)
        return add_search_label(parser, op, arg + 1, index);
    value = (int)ice_strtol(arg + 1, &endptr);
    if (*endptr)
        return false;
    op->args[index] = value;
    return true;
}

static bool add_ind(parser_t *parser, parser_op_t *op, uint8_t index, char *arg)
{
    char *endptr;
    int value = (int)ice_strtol(arg, &endptr);

    if (*endptr)
        return false;
    op->type |= IND_CODE << GET_OFFSET(index);
    parser->tmp_size_bits += IND_SIZE;
    if (arg[0] == LABEL_CHAR)
        return add_search_label(parser, op, arg, index);
    op->args[index] = value;
    return true;
}

bool add_argument(parser_t *parser, parser_op_t *op, uint8_t index, char *arg)
{
    if (arg[0] == REG_CHAR)
        return add_reg(parser, op, index, arg);
    if (arg[0] == DIRECT_CHAR)
        return add_dir(parser, op, index, arg);
    return add_ind(parser, op, index, arg);
}
