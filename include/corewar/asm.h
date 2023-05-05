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
    uint8_t type;
    char *args[4];
    uint8_t arg_count;
} precoded_op_t;

    #define OP current_op->op
    #define ARGS current_op->args
    #define ARG_COUNT current_op->arg_count

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

typedef struct parse_s {
    list_t *op;
    list_t *label;
    uint32_t count;
} parse_t;

    #define L_OP (parse->op)
    #define L_LABEL (parse->label)
    #define T_COUNT (parse->count)

//
// ASM
//

/**
 * @brief The main function of the asm
 *
 * @param file_path The file path
 * @return true If the asm worked
 * @return false If the asm failed
 */
bool asm_f(char *file_path);

//
// Lexer
//

/**
 * @brief Get the file content from a file path
 * @brief and remove all the skipped chars
 *
 * @param header The header
 * @param filepath The file path
 * @return char** The file content
 */
char **lexer(header_t **header, char *filepath);

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
// Parse
//

parse_t *create_parse(void);

//
// Extract
//

void extract(char **lines);

//
// Label
//

bool create_label(parse_t *parse, token_t *token);

//
// Operator
//

bool create_operator(parse_t *parse, token_t *token,
    precoded_op_t **current_op);

//
// Display
//

void display_token(parse_t *parse);

#endif /* !COREWAR_ASM_H */
