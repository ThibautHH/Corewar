/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** parse_args
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ice/string.h"
#include "ice/int.h"
#include "ice/printf.h"
#include "corewar/corewar.h"

#ifndef CHAMPION_INIT
    #ifndef CHAMPION_INFO
    struct champion_info_s {
        char *name;
        char *comment;
        size_t size;
        uint8_t *code;
        size_t load_address;
        size_t number;
    };
    #endif /* !CHAMPION_INFO */

void champion_init(champion_t *champion, struct champion_info_s *info);
#endif /* !CHAMPION_INIT */

#ifndef PARSING
    #ifndef FLAG_STRUCT
    struct flag_t {
        char *flag;
        bool *boolean;
        size_t *value;
    };
    #endif /* !FLAG_STRUCT */

    #ifndef VAR_STRUCT
    struct var_t {
        size_t current_champion_address;
        int current_champion_number;
        bool address_specified;
        int ret;
    };
    #endif /* !VAR_STRUCT */
#endif /* !PARSING */


static void parse_file(char *filename, champion_t *champion)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL) exit(84);
    uint32_t magic;
    fread(&magic, sizeof(magic), 1, file);
    magic = ENDIAN(magic);
    if (magic != COREWAR_EXEC_MAGIC) exit(84);
    champion->name = malloc(PROG_NAME_LENGTH + 1);
    fread(champion->name, PROG_NAME_LENGTH, 1, file);
    champion->name[PROG_NAME_LENGTH] = '\0';
    fseek(file, 4, SEEK_CUR);
    fread(&champion->size, sizeof(champion->size), 1, file);
    champion->size = (size_t)ENDIAN(champion->size);
    champion->comment = malloc(COMMENT_LENGTH + 1);
    fread(champion->comment, COMMENT_LENGTH, 1, file);
    champion->comment[COMMENT_LENGTH] = '\0';
    fseek(file, 4, SEEK_CUR);
    champion->code = malloc(champion->size);
    fread(champion->code, champion->size, 1, file);
    fclose(file);
}

static void error_flag(char *flag)
{
    char *error_message = "Error: invalid flag usage: ";
    fwrite(error_message, 1, ice_strlen(error_message), stderr);
    fwrite(flag, 1, ice_strlen(flag), stderr);
    fwrite("\n", 1, 1, stderr);
    exit(84);
}

static int handle_normal_flag(struct flag_t *flags,
    int *i, int ac, char **av)
{
    for (int j = 0; j < 3; j++) {
        if (!ice_strcmp(av[*i], flags[j].flag)) {
            (flags[j].boolean) ? *flags[j].boolean = true : 0;
            (*i + 1 >= ac) ? error_flag(flags[j].flag) : 0;
            *flags[j].value = ice_atoi(av[++(*i)]);
            *i += 1;
            return (0);
        }
    }
    return (1);
}

static size_t ternary_memory_champion(struct var_t v, champion_t *champion)
{
    return (!v.address_specified) ? (v.current_champion_address +
            champion->size) % MEM_SIZE : v.current_champion_address % MEM_SIZE;
}

void parse_args(int ac, char **av, vm_t *vm)
{
    struct var_t v = {0, 1, false, 0};
    struct { char *flag; bool *boolean; void *value; } flags[] = {
        {"-dump", &vm->dump, &vm->dump_cycle},
        {"-n", NULL, &v.current_champion_number},
        {"-a", &v.address_specified, &v.current_champion_address},
    };
    for (int i = 1; i < ac; i++) {
        for (int j = 0; flags[j].flag != NULL; j++)
            v.ret = handle_normal_flag((struct flag_t*)flags, &i, ac, av);
        if (v.ret == 0) continue;
        champion_t *champion = malloc(sizeof(champion_t));
        parse_file(av[i], champion);
        v.current_champion_address = ternary_memory_champion(v, champion);
        champion_init(champion, (struct champion_info_s[]){{champion->name,
            champion->comment, champion->size, champion->code,
            v.current_champion_address, v.current_champion_number}});
        LIST_INSERT_HEAD(&vm->champ_list, champion, entries);
        v.current_champion_number++;
        v.address_specified = false;
    }
}
