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

    #define REG_CHAR       'r'      /* character that indicate a register */

    #define COMMENT_CHAR   '#'
    #define LABEL_CHAR     ':'
    #define DIRECT_CHAR    '%'
    #define SEPARATOR_CHAR ','

    #define SKIPPED_CHARS " \t\n\0"
    #define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

    #define NAME_CMD_STRING    ".name"
    #define COMMENT_CMD_STRING ".comment"

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

typedef struct op_s {
    char mnemonic[8];
    uint8_t nbr_args;
    arg_type_t type[MAX_ARGS_NUMBER];
    uint8_t code;
    uint16_t nbr_cycles;
} op_t;

/*
** size (in bytes)
*/
    #define OP_SIZE 1

    #define IND_SIZE 2
    #define DIR_SIZE 4
    #define REG_SIZE DIR_SIZE

    #define REG_CODE 1
    #define DIR_CODE 2
    #define IND_CODE 3

    #define OP_TAB_SIZE 21

static const op_t op_tab[OP_TAB_SIZE] = {
    /*
    ** Mnemonic,
    ** Number of arguments, {
    **   Type of argument[,
    **   Type of argument...]
    ** },
    ** Code,
    ** Number of cycles
    */
    {
        "live", // Live
        1, {T_DIR}, // live <player number>
        1,
        10
    },
    {
        "ld",   // Load memory into register
        2, {
            T_DIR | T_IND,
            T_REG
        },          // ld <val|addr>,<reg>
        2,
        5
    },
    {
        "st",   // Copy register value into memory/register
        2, {
            T_REG,
            T_IND | T_REG
        },          // st <reg>,<addr|reg>
        3,
        5
    },
    {
        "add",  // Sum two registers and store the result in a register
        3, {
            T_REG,
            T_REG,
            T_REG
        },          // add <reg>,<reg>,<reg>
        4,
        10
    },
    {
        "sub",  // Subtract two registers and store the result in a register
        3, {
            T_REG,
            T_REG,
            T_REG
        },          // sub <reg>,<reg>,<reg>
        5,
        10
    },
    {
        "and",  // Bitwise AND of two register/value/memory at address
                // and store the result in a register
        3, {
            T_REG | T_DIR | T_IND,
            T_REG | T_DIR | T_IND,
            T_REG
        },          // and <reg|val|addr>,<reg|val|addr>,<reg>
        6,
        6
    },
    {
        "or",   // Bitwise OR of two register/value/memory at address
                // and store the result in a register
        3, {
            T_REG | T_IND | T_DIR,
            T_REG | T_IND | T_DIR,
            T_REG
        },          // or <reg|val|addr>,<reg|val|addr>,<reg>
        7,
        6
    },
    {
        "xor",  // Bitwise XOR of two register/value/memory at address
                // and store the result in a register
        3, {
            T_REG | T_IND | T_DIR,
            T_REG | T_IND | T_DIR,
            T_REG
        },          // xor <reg|val|addr>,<reg|val|addr>,<reg>
        8,
        6
    },
    {
        "zjmp", // Jump to address (set PC to value)
        1, {T_DIR}, // zjmp <val>
        9,
        20
    },
    {
        "ldi",
        3, {
            T_REG | T_DIR | T_IND,
            T_DIR | T_REG,
            T_REG
        },
        10,
        25
    },
    {
        "sti",
        3, {
            T_REG,
            T_REG | T_DIR | T_IND,
            T_DIR | T_REG
        },
        11,
        25
    },
    {
        "fork",
        1, {T_DIR},
        12,
        800
    },
    {
        "lld",
        2, {
            T_DIR | T_IND,
            T_REG
        },
        13,
        10
    },
    {
        "lldi",
        3, {
            T_REG | T_DIR | T_IND,
            T_DIR | T_REG,
            T_REG
        },
        14,
        50
    },
    {
        "lfork",
        1, {T_DIR},
        15,
        1000
    },
    {
        "aff",
        1, {T_REG},
        16,
        2
    }
};

    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH   2048

    #define COREWAR_EXEC_MAGIC 0xea83f3u

typedef struct header_s {
    int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    int prog_size;
    char comment[COMMENT_LENGTH + 1];
} header_t;

    #define CYCLE_TO_DIE 1536u    // number of cycle before being declared dead
    #define CYCLE_DELTA  5u
    #define NBR_LIVE     40u

#endif /* !OP_H_ */
