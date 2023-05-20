/*
** EPITECH PROJECT, 2022
** Corewar/asm
** File description:
** Main compilation functions
*/

#include "asm.h"

static void grow_buffer(asm_t *ctx)
{
    BUFFER = realloc(BUFFER, BUFFERSZ + sizeof(char) * READ_SIZE);
    if (!BUFFER)
        quit(ctx, 84);
    HEAD = &BUFFER[BUFFERSZ];
    BUFFERSZ += READ_SIZE;
}

static void load_file(asm_t *ctx)
{
    size_t size;

    for (grow_buffer(ctx); (size = READ_SRC) == READ_SIZE;)
        grow_buffer(ctx);
    if (ferror(F(IN)))
        quit(ctx, 84);
    BUFFERSZ += size;
    BUFFER[BUFFERSZ] = '\0';
    HEAD = BUFFER;
}

static void create_header(asm_t *ctx)
{
    size_t size = 0;

    if (SKIP(WHTSPC) && !IS_CMD(NAME))
        PARSE_ERR("Champion name unspecified"), quit(ctx, 84);
    if (SKIP(SPC) && ISNT_STRING)
        PARSE_ERR("Champion name unspecified"), quit(ctx, 84);
    if (size > PROG_NAME_LENGTH)
        PARSE_ERR("Champion name too long"), quit(ctx, 84);
    strncpy2(ctx->header.prog_name, HEAD, size);
    ADVN(size + 1);
    if (SKIP(WHTSPC) && !IS_CMD(COMMENT))
        PARSE_ERR("Champion comment unspecified"), quit(ctx, 84);
    if (SKIP(SPC) && ISNT_STRING)
        PARSE_ERR("Champion comment unspecified"), quit(ctx, 84);
    if (size > COMMENT_LENGTH)
        PARSE_ERR("Champion comment too long"), quit(ctx, 84);
    strncpy2(ctx->header.comment, HEAD, size);
    ADVN(size + 1);
}

static void parse(asm_t *ctx)
{
    create_header(ctx);
    for (SKIP(WHTSPC); *HEAD; SKIP(WHTSPC)) {
        if (IS_CMD(NAME) || IS_CMD(COMMENT))
            PARSE_ERR("Command in the middle of the file"), quit(ctx, 84);
    }
}

void compile(asm_t *ctx)
{
    load_file(ctx);
    parse(ctx);
}
