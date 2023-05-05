/*
** EPITECH PROJECT, 2022
** corewar
** File description:
** asm.h
*/

#ifndef COREWAR_ASM_H
    #define COREWAR_ASM_H

    #include <stdbool.h>

    #include "corewar/op.h"

    #define STRING_CHAR '\"'
    #define READ_SIZE 4096

typedef struct precoded_op_s {
    op_t op;
    uint8_t type;
    char *args[4];
    uint8_t arg_count;
} precoded_op_t;

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
// Extract
//

void extract(char **lines);

//
// Label
//

bool label_is_valid(char *label);

#endif /* !COREWAR_ASM_H */
