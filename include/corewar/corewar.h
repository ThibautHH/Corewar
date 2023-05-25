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
    #include <stdbool.h>
    #include <stdlib.h>

    #define UNUSED __attribute__((unused))

    #define FLAG_COUNT 3u

    #define IS_NUM(c) (c >= '0' && c <= '9')

    #define END32_CENTRE(x) (((x) & 0xFF00) << 8) | (((x) >> 8) & 0xFF00)
    #define END32(x) ((x) << 24 | END32_CENTRE(x) | (x) >> 24)
    #define END16(x) ((x) << 8 | (x) >> 8)

typedef uint32_t u32_t;
typedef uint16_t u16_t;

    #define ENDIAN(x) (_Generic ((x), u32_t : END32(x), u16_t : END16(x)))

    #define PROC_REG(p, n) (*((uint32_t *)(&((p)->regs[(n) - 1]))))

    #define FIRST_CHAMP (TAILQ_FIRST(&vm->champ_list))
    #define LAST_CHAMP (TAILQ_LAST(&vm->champ_list, champions_s))

typedef struct process_s {
    TAILQ_ENTRY(process_s) entries;
    uint8_t *pc;
    struct {
        uint8_t bytes[REG_SIZE];
    } regs[REG_NUMBER];
    uint8_t carry;
} process_t;

typedef struct champion_s {
    TAILQ_ENTRY(champion_s) entries;
    char name[PROG_NAME_LENGTH + 1];
    char comment[COMMENT_LENGTH + 1];
    uint32_t size;
    uint8_t *code;
    size_t load_address;
    uint16_t number;
    TAILQ_HEAD(, process_s) process_list;
} champion_t;

typedef struct vm_s {
    TAILQ_HEAD(champions_s, champion_s) champ_list;
    uint8_t memory[MEM_SIZE];
    size_t cycle;
    size_t cycle_to_die;
    size_t nb_live;
    size_t nb_process;
    size_t nb_champ;
    bool dump;
    size_t dump_cycle;
} vm_t;

typedef struct flag_s {
    char *flag;
    bool *boolean;
    size_t *value;
} flag_t;

#endif /* !COREWAR_COREWAR_H */
