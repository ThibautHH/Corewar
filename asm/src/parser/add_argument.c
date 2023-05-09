/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** add_argument.c
*/

#include "ice/int.h"
#include "corewar/asm.h"

/*
 * TODO: Label handling
 */

static bool add_reg(code_t *code, precode_t *op, uint8_t index, char *arg)
{
    char *endptr;
    int64_t value = ice_strtol(arg + 1, &endptr);

    if (*endptr || value < 0 || value > REG_NUMBER)
        return false;
    op->type |= T_REG << GET_OFFSET(index);
    SIZE_BITS += REG_SIZE;
    op->args[index] = value;
    return true;
}

static bool add_dir(code_t *code, precode_t *op, uint8_t index, char *arg)
{
    char *endptr;
    int64_t value;

    op->type |= T_DIR << GET_OFFSET(index);
    SIZE_BITS += DIR_SIZE;
    if (arg[1] == LABEL_CHAR) {
        op->args[index] = 0;
        return true;
    }
    value = ice_strtol(arg + 1, &endptr);
    if (*endptr)
        return false;
    op->args[index] = value;
    return true;
}

static bool add_ind(code_t *code, precode_t *op, uint8_t index, char *arg)
{
    char *endptr;
    int64_t value = ice_strtol(arg, &endptr);

    if (*endptr)
        return false;
    op->type |= T_IND << GET_OFFSET(index);
    SIZE_BITS += IND_SIZE;
    op->args[index] = value;
    return true;
}

bool add_argument(code_t *code, precode_t *op, uint8_t index, char *arg)
{
    if (arg[0] == REG_CHAR)
        return add_reg(code, op, index, arg);
    if (arg[0] == DIRECT_CHAR)
        return add_dir(code, op, index, arg);
    return add_ind(code, op, index, arg);
}
