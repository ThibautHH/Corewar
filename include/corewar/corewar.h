/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** corewar.h
*/

#ifndef COREWAR_COREWAR_H
    #define COREWAR_COREWAR_H

    #define IS_NUM(c) (c >= '0' && c <= '9')
    #define IS_STR_NUM(str) (str[0] == '-' ? IS_NUM(str[1]) : IS_NUM(str[0]))

typedef struct arg_parse_s {
    int dump;
    int prog_number;
    int load_address;
} arg_parse_t;

typedef struct corewar_s {
    arg_parse_t arg_parse;
} corewar_t;

int parse_arg(corewar_t *corewar, int ac, char **av);

#endif /* !COREWAR_COREWAR_H */
