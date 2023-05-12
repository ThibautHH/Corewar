/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** corewar.h
*/

#ifndef COREWAR_COREWAR_H
    #define COREWAR_COREWAR_H

    #include "op.h"
    #include <sys/queue.h>

    #define IS_NUM(c) (c >= '0' && c <= '9')

typedef struct arg_parse_s {
    int dump;
    int prog_number;
    int load_address;
} arg_parse_t;

typedef struct champion_s {
    header_t header;
    char *prog;
    TAILQ_ENTRY(champion_s) next;
} champion_t;

typedef struct corewar_s {
    arg_parse_t arg_parse;
    TAILQ_HEAD(champion_head_s, champion_s) champions;
} corewar_t;

int parse_arg(corewar_t *corewar, int ac, char **av);

#endif /* !COREWAR_COREWAR_H */
