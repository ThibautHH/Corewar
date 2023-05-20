/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** Assembler definitions
*/

#ifndef OP_H_
    #define OP_H_

    #include <stddef.h>
    #include <stdint.h>

    #define MEM_SIZE        (6u * 1024u)
    #define IDX_MOD         512u    /* modulo of the index < */
    #define MAX_ARGS_NUMBER 4u      /* this may not be changed 2^*IND_SIZE */

    #define REG_CHAR       'r'      /* character that indicates a register */
    #define COMMENT_CHAR   '#'
    #define LABEL_CHAR     ':'
    #define DIRECT_CHAR    '%'
    #define SEPARATOR_CHAR ','
    #define STRING_CHAR    '"'

    #define SKIPPED_CHARS " \t"
    #define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

    #define NAME_CMD_STRING    ".name"
    #define NAME_CMD_LEN       5
    #define COMMENT_CMD_STRING ".comment"
    #define COMMENT_CMD_LEN    8

    #define REG_NUMBER 16   /* r1 to r(n) */

    #define T_REG 0b0001u   /* Register */
    #define T_DIR 0b0010u   /* Direct
                               `ld #1,r1`:
                               Put 1 into r1 */
    #define T_IND 0b0100u   /* Indirect always relative
                               `ld 1,r1`:
                               Put the 4 bytes at address (1+pc) into r1 */
    #define T_LAB 0b1000u   /* Label */

typedef unsigned char arg_type_t;

typedef enum op_code_e {
    OP_NONE = 0,
    OP_LIVE = 1,
    OP_LD = 2,
    OP_ST = 3,
    OP_ADD = 4,
    OP_SUB = 5,
    OP_AND = 6,
    OP_OR = 7,
    OP_XOR = 8,
    OP_ZJMP = 9,
    OP_LDI = 10,
    OP_STI = 11,
    OP_FORK = 12,
    OP_LLD = 13,
    OP_LLDI = 14,
    OP_LFORK = 15,
    OP_AFF = 16
} op_code_t;

typedef struct op_s {
    op_code_t code;
    char mnemonic[8];
    uint8_t nbr_args;
    arg_type_t type[MAX_ARGS_NUMBER];
    uint16_t nbr_cycles;
} op_t;

    #define IND_SIZE 2
    #define DIR_SIZE 4
    #define REG_SIZE 1

    #define OP_TAB_SIZE 21

static const op_t op_tab[OP_TAB_SIZE] = {
    /*
    ** Code,
    ** Mnemonic,
    ** Number of arguments, {
    **   Type of argument[,
    **   Type of argument...]
    ** },
    ** Number of cycles
    */
    {
        OP_LIVE,
        "live", // Live
        1, {T_DIR}, // live <player number>
        10
    },
    {
        OP_LD,
        "ld",   // Load memory into register
        2, {
            T_DIR | T_IND,
            T_REG
        },          // ld <val|addr>,<reg>
        5
    },
    {
        OP_ST,
        "st",   // Copy register value into memory/register
        2, {
            T_REG,
            T_IND | T_REG
        },          // st <reg>,<addr|reg>
        5
    },
    {
        OP_ADD,
        "add",  // Sum two registers and store the result in a register
        3, {
            T_REG,
            T_REG,
            T_REG
        },          // add <reg>,<reg>,<reg>
        10
    },
    {
        OP_SUB,
        "sub",  // Subtract two registers and store the result in a register
        3, {
            T_REG,
            T_REG,
            T_REG
        },          // sub <reg>,<reg>,<reg>
        10
    },
    {
        OP_AND,
        "and",  // Bitwise AND of two register/value/memory at address
                // and store the result in a register
        3, {
            T_REG | T_DIR | T_IND,
            T_REG | T_DIR | T_IND,
            T_REG
        },          // and <reg|val|addr>,<reg|val|addr>,<reg>
        6
    },
    {
        OP_OR,
        "or",   // Bitwise OR of two register/value/memory at address
                // and store the result in a register
        3, {
            T_REG | T_IND | T_DIR,
            T_REG | T_IND | T_DIR,
            T_REG
        },          // or <reg|val|addr>,<reg|val|addr>,<reg>
        6
    },
    {
        OP_XOR,
        "xor",  // Bitwise XOR of two register/value/memory at address
                // and store the result in a register
        3, {
            T_REG | T_IND | T_DIR,
            T_REG | T_IND | T_DIR,
            T_REG
        },          // xor <reg|val|addr>,<reg|val|addr>,<reg>
        6
    },
    {
        OP_ZJMP,
        "zjmp", // Jump to address (set PC to value)
        1, {T_DIR}, // zjmp <val>
        20
    },
    {
        OP_LDI,
        "ldi",
        3, {
            T_REG | T_DIR | T_IND,
            T_DIR | T_REG,
            T_REG
        },
        25
    },
    {
        OP_STI,
        "sti",
        3, {
            T_REG,
            T_REG | T_DIR | T_IND,
            T_DIR | T_REG
        },
        25
    },
    {
        OP_FORK,
        "fork",
        1, {T_DIR},
        800
    },
    {
        OP_LLD,
        "lld",
        2, {
            T_DIR | T_IND,
            T_REG
        },
        10
    },
    {
        OP_LLDI,
        "lldi",
        3, {
            T_REG | T_DIR | T_IND,
            T_DIR | T_REG,
            T_REG
        },
        50
    },
    {
        OP_LFORK,
        "lfork",
        1, {T_DIR},
        1000
    },
    {
        OP_AFF,
        "aff",
        1, {T_REG},
        2
    }
};

    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH   2048

    #define COREWAR_EXEC_MAGIC 0xea83f3u

typedef struct header_s {
    uint32_t magic;
    char prog_name[PROG_NAME_LENGTH];
    size_t prog_size;
    char comment[COMMENT_LENGTH];
} header_t;

    #define CYCLE_TO_DIE 1536u    // number of cycle before being declared dead
    #define CYCLE_DELTA  5u
    #define NBR_LIVE     40u

#endif /* !OP_H_ */
