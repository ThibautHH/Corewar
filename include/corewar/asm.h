/*
** EPITECH PROJECT, 2022
** Corewar/asm
** File description:
** Main header file
*/

#ifndef COREWAR_ASM_H
    #define COREWAR_ASM_H

    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include "ice/printf.h"
    #include "op.h"

    #define FILEN (ctx->file_name)
    #define F(side) (ctx->files[STD##side##_FILENO])

typedef struct precoded_op_s {
    op_code_t code;
    arg_type_t arg_types[MAX_ARGS_NUMBER];
    uint64_t args[MAX_ARGS_NUMBER];
} precoded_op_t;

typedef struct asm_s {
    FILE *files[2];
    char *file_name;
} asm_t;

bool open_files(asm_t *ctx);
void __attribute__((noreturn)) quit(asm_t *ctx, int status);

#endif /* !COREWAR_ASM_H */
