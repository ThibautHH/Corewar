/*
** EPITECH PROJECT, 2022
** Corewar/asm
** File description:
** Main header file
*/

#ifndef COREWAR_ASM_H
    #define COREWAR_ASM_H

    #include <stdbool.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include <sys/types.h>

    #include "ice/printf.h"
    #include "ice/string.h"

    #include "op.h"
    #include "asm/strutils.h"

    #define READ_SIZE 4096

    #define IS_SPC(c) ((c) == ' ' || (c) == '\t')
    #define IS_NL(c) ((c) == '\n')
    #define IS_WHTSPC(c) (IS_SPC(c) || IS_NL(c))

    #define END32_CENTRE(x) ((x) & 0xFF00) << 8 | ((x) >> 8) & 0xFF00
    #define END32(x) ((x) << 24 | END32_CENTRE(x) | (x) >> 24)
    #define END16(x) ((x) << 8 | (x) >> 8)
    #define ENDIAN(x) (_Generic((x), uint32_t: END32(x), uint16_t: END16(x)))

    #define OP(id) (op_tab[(id) - 1])
    #define OPSTR(id) (OP(id).mnemonic)

    #define ADV (IS_NL(*HEAD) ? (HEAD++, LINE++, (COL = 1)) : (HEAD++, COL++))
    #define ADVN(n) ({for (size_t i = 0; i < n; i++) ADV; 1;})
    #define SKIP(spc) ({while (IS_##spc(*HEAD)) ADV; 1;})

    #define CMD_STRCMP(x) (strncmp2(HEAD, x##_CMD_STRING, x##_CMD_LEN))
    #define IS_SPACE_AFTER_CMD(x) (ADVN(x##_CMD_LEN) && IS_SPC(*HEAD))
    #define IS_CMD(what) (!CMD_STRCMP(what) && IS_SPACE_AFTER_CMD(what))
    #define TO_NEXT_QUOTE (size = strtil(HEAD, STRING_CHAR))
    #define NO_END_QUOTE (!ADV || TO_NEXT_QUOTE >= strtil(HEAD, '\n'))
    #define ISNT_STRING *HEAD != STRING_CHAR || NO_END_QUOTE

    #define OP_LEN(id) size_t l = ice_strlen(OPSTR(id))
    #define OP_STRCMP(id) (strncmp2(HEAD, OPSTR(id), l))
    #define IS_OP(id) ({OP_LEN(id); (OP_STRCMP(id) && ADVN(l) && IS_SPC(*HEAD));})

    #define READ_SRC fread(HEAD, sizeof(char), READ_SIZE, F(IN))

    #define FILEN (ctx->file_name)
    #define CMD (ctx->cmd)
    #define BUFFER (ctx->buffer)
    #define BUFFERSZ (ctx->buffer_size)
    #define HEAD (ctx->head)
    #define LINE (ctx->line)
    #define COL (ctx->col)
    #define F(side) (ctx->files[STD##side##_FILENO])
    #define PARSE_ERR_FMT "%s: %s:%lu:%lu: %s.\n", CMD, FILEN, LINE, COL
    #define PARSE_ERR(s) (ice_dprintf(STDERR_FILENO, PARSE_ERR_FMT, (s)))

typedef struct precoded_op_s {
    op_code_t code;
    arg_type_t arg_types[MAX_ARGS_NUMBER];
    uint64_t args[MAX_ARGS_NUMBER];
} precoded_op_t;

typedef struct asm_s {
    FILE *files[2];
    size_t buffer_size;
    size_t line, col;
    char *buffer, *head;
    char *cmd, *file_name;
    header_t header;
} asm_t;

bool open_files(asm_t *ctx);
void __attribute__((noreturn)) quit(asm_t *ctx, int status);

#endif /* !COREWAR_ASM_H */
