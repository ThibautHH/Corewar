/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** asm.h
*/

#ifndef COREWAR_ASM_H
    #define COREWAR_ASM_H

    #include "op.h"

typedef struct precoded_op_s {
    op_code_t code;
    arg_type_t arg_types[MAX_ARGS_NUMBER];
    uint64_t args[MAX_ARGS_NUMBER];
} precoded_op_t;

#endif /* !COREWAR_ASM_H */
