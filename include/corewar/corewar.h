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
    #include <sys/types.h>
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>

    #define UNUSED __attribute__((unused))

    #define FLAG_COUNT 3u

    #define SMCLN ;
    #define TQFSIT(v, f, t)   (v) = (t)
    #define TQFSCND2(v, f, t) ((t) = TAILQ_NEXT(v, f), 1)
    #define TQFSCND(v, h, f, t) (v) && TQFSCND2(v, f, t)SMCLN TQFSIT(v, f, t)
    #define TQFS(v, h, f, t) (v) = TAILQ_FIRST(h)SMCLN TQFSCND(v, h, f, t)
    #define	TAILQ_FOREACH_SAFE(v, h, f, t) for (TQFS(v, h, f, t))

    #define END32_CENTRE(x) (((x) & 0xFF00) << 8) | (((x) >> 8) & 0xFF00)
    #define END32(x) ((x) << 24 | END32_CENTRE(x) | (x) >> 24)
    #define END16(x) ((x) << 8 | (x) >> 8)
    #define END(x) (_Generic ((x), uint32_t : END32(x), uint16_t : END16(x)))

extern const uint16_t endianness;

    #define IS_LE (*((uint8_t *)(&endianness)))

    #define BYTE_SHIFT ((IS_LE ? (n - i - 1) : i) * 8)

    #define PROC_REG(p, n) (*((uint32_t *)(&((p)->regs[(n) - 1]))))

    #define FIRST_CHAMP (TAILQ_FIRST(&vm->champ_list))
    #define LAST_CHAMP (TAILQ_LAST(&vm->champ_list, champions_s))

    #define CHAMP (vm->current_champ)
    #define PROC (vm->current_process)
    #define INST (vm->inst_pc)

    #define NEXT_BYTE (get_next_byte(vm))
    #define ARGT(n) ((args_code >> (8 - (n) * 2)) & 0b11u)
    #define VAL_TYPE(t, v) ((t) == DIR_CODE ? v.index : v.direct)

typedef struct process_s {
    TAILQ_ENTRY(process_s) entries;
    uint8_t *pc;
    struct {
        uint8_t bytes[REG_SIZE];
    } regs[REG_NUMBER];
    uint8_t carry;
    uint16_t cycles_left;
} process_t;

typedef struct champion_s {
    TAILQ_ENTRY(champion_s) entries;
    char name[PROG_NAME_LENGTH + 1];
    char comment[COMMENT_LENGTH + 1];
    uint32_t size;
    uint8_t *code;
    ssize_t load_address;
    int32_t number;
    bool alive;
    TAILQ_HEAD(, process_s) process_list;
} champion_t;

typedef struct vm_s {
    TAILQ_HEAD(champions_s, champion_s) champ_list;
    champion_t *current_champ;
    process_t *current_process;
    uint8_t *inst_pc;
    uint8_t memory[MEM_SIZE];
    size_t cycle;
    size_t cycle_to_die;
    size_t live_call_count;
    size_t nb_process;
    size_t nb_champ;
    bool dump;
    size_t dump_cycle;
} vm_t;

typedef void (*instruction_t)(vm_t *);

typedef union val_u {
    int16_t index;
    int32_t direct;
} val_t;

typedef struct flag_s {
    char *flag;
    bool *boolean;
    size_t *value;
} flag_t;

static inline void next_swap(vm_t *vm, champion_t *i, bool *swapped)
{
    champion_t *next = TAILQ_NEXT(i, entries);

    if (i->number <= next->number)
        return;
    TAILQ_REMOVE(&vm->champ_list, i, entries);
    TAILQ_INSERT_AFTER(&vm->champ_list, next, i, entries);
    *swapped = 1;
}

static inline void prev_swap(vm_t *vm, champion_t *i, bool *swapped)
{
    champion_t *prev = TAILQ_PREV(i, champions_s, entries);

    if (i->number >= prev->number)
        return;
    TAILQ_REMOVE(&vm->champ_list, i, entries);
    TAILQ_INSERT_BEFORE(prev, i, entries);
    *swapped = 1;
}

static inline uint8_t get_next_byte(vm_t *vm)
{
    uint8_t byte = *(PROC->pc++);

    if (PROC->pc == vm->memory + MEM_SIZE)
        PROC->pc = vm->memory;
    return byte;
}

UNUSED static const char *malloc_failed_error =
    "Vm failed to malloc, exiting.\n";

void kill_process(vm_t *vm);
void set_value(vm_t *vm, uint8_t type, int32_t value, bool set_carry);
val_t get_value(vm_t *vm, uint8_t arg_type, bool is_index, bool long_mode);

#endif /* !COREWAR_COREWAR_H */
