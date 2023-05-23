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
    #define ALLOC_SIZE 1024

    #define END32_CENTRE(x) ((((x) & 0xFF00) << 8) | (((x) >> 8) & 0xFF00))
    #define END32(x) (((x) << 24) | END32_CENTRE(x) | ((x) >> 24))
    #define END16(x) (((x) << 8) | ((x) >> 8))

typedef uint32_t u32_t;
typedef uint16_t u16_t;

    #define ENDIAN(x) (_Generic ((x), u32_t : END32(x), u16_t : END16(x)))

typedef struct lexer_op_s {
    op_t op;
    char *args[MAX_ARGS_NUMBER];
    uint8_t arg_count;
} lexer_op_t;

typedef struct strlen_s {
    char *str;
    uint32_t len;
} strlen_t;

typedef strlen_t label_t;
typedef strlen_t token_t;

typedef struct lexer_s {
    header_t *header;
    list_t *op;
    list_t *label;
    uint32_t count;
} lexer_t;

typedef struct parser_op_s {
    char *mnemonic;
    uint8_t code;
    uint8_t type;
    uint32_t args[MAX_ARGS_NUMBER];
} parser_op_t;

    #define GET_OFFSET(index) ((MAX_ARGS_NUMBER - index - 1) * 2)

typedef struct search_label_s {
    char *name;
    uint32_t index;
    uint32_t *ptr;
} search_label_t;

typedef struct parser_s {
    header_t *header;
    list_t *precode;
    list_t *labels;
    list_t *search_labels;
    uint32_t size_bits;
    uint32_t tmp_size_bits;
    uint32_t size;
} parser_t;

//static const char *index[] = {
//    "zjmp",
//    "ldi",
//    "sti",
//    "fork",
//};

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
lexer_t *lexer_f(char *filepath);

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

parser_t *parser_f(lexer_t *lexer);

void destroy_lexer(lexer_t *lexer);

//
// Extract
//

bool extract(lexer_t *lexer, char **lines);

//
// Label
//

bool create_label(lexer_t *lexer, token_t *token);

//
// Operator
//

bool create_operator(token_t *token, lexer_op_t **op);

//
// Argument
//

bool add_argument(parser_t *parser, parser_op_t *op, uint8_t index, char *arg);

//
// Display
//

bool writer(char *filepath, parser_t *parser);

char *get_filename(char *filepath);

void update_token(token_t *token);

#endif /* !COREWAR_ASM_H */
