/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** asm.h
*/

#ifndef COREWAR_ASM_H
    #define COREWAR_ASM_H

    #include <stdbool.h>

    #include "list.h"
    #include "corewar/op.h"

    #define STRING_CHAR '\"'
    #define READ_SIZE 4096

typedef struct precoded_op_s {
    op_t op;
    char *args[MAX_ARGS_NUMBER];
    uint8_t arg_count;
} precoded_op_t;

    #define OP (current_op->op)
    #define ARGS (current_op->args)
    #define ARG_COUNT (current_op->arg_count)

typedef struct precoded_label_s {
    char *name;
    uint32_t index;
} precoded_label_t;

typedef struct token_s {
    char *str;
    uint32_t len;
} token_t;

    #define TOKEN (token.str)
    #define LEN (token.len)

    #define P_TOKEN (token->str)
    #define P_LEN (token->len)

typedef struct parser_s {
    list_t *op;
    list_t *label;
    uint32_t count;
} parser_t;

    #define L_OP (parser->op)
    #define L_LABEL (parser->label)
    #define T_COUNT (parser->count)

typedef struct precode_s {
    uint8_t op;
    uint8_t type;
    uint64_t args[MAX_ARGS_NUMBER];
} precode_t;

    #define GET_OFFSET(index) ((MAX_ARGS_NUMBER - index - 1) * 2)

typedef struct label_s {
    char *name;
    uint32_t index;
    uint32_t *ptr;
} label_t;

typedef struct code_s {
    list_t *precode;
    uint32_t size_bits;
    uint32_t size;
} code_t;

    #define PRECODE (code->precode)
    #define SIZE_BITS (code->size_bits)
    #define SIZE (code->size)

//
// ASM
//

/**
 * @brief The main function of the asm
 *
 * @param filepath The file path
 * @return true If the asm worked
 * @return false If the asm failed
 */
bool asm_f(char *filepath);

//
// Lexer
//

/**
 * @brief Get the file content from a file path
 * @brief and remove all the skipped chars
 *
 * @param header The header
 * @param filepath The file path
 */
parser_t *lexer(header_t **header, char *filepath);

void destroy_lexer(char *file, void *head);

//
// Token
//

/**
 * @brief Get the next token
 *
 * @param str The string to skip
 * @return char* The string without skipped chars
 */
char *token_skip_chars(char *str);

/**
 * @brief Skip all the skipped chars
 *
 * @param str The string to skip
 * @return char* The string without skipped chars
 */
uint32_t token_get_len(const char *str);

//
// Header
//

/**
 * @brief Create the header
 *
 * @param lines The file content
 * @return header_t* The header
 */
header_t *create_header(char ***lines);

//
// Parser
//

parser_t *create_parser(void);

code_t *parse(parser_t *parser);

void destroy_parser(parser_t *parser);

//
// Extract
//

parser_t *extract(char **lines);

//
// Label
//

bool create_label(parser_t *parser, token_t *token);

//
// Operator
//

bool create_operator(token_t *token, precoded_op_t **current_op);

//
// Argument
//

bool add_argument(code_t *code, precode_t *op, uint8_t index, char *arg);

//
// Display
//

void writer(char *filepath, header_t *header,code_t *code);

void display_token(parser_t *parser);

#endif /* !COREWAR_ASM_H */
