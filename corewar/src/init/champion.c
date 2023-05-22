/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** champion
*/

#include "corewar/corewar.h"
#include "ice/memory.h"
#include "ice/string.h"

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

void champion_init(champion_t *champion, struct champion_info_s *info)
{
    champion->name = ice_strdup(info->name);
    champion->comment = ice_strdup(info->comment);
    champion->size = info->size;
    champion->code = malloc(info->size);
    ice_memcpy(champion->code, info->code, info->size);
    champion->load_address = info->load_address;
    champion->number = info->number;
    TAILQ_INIT(&champion->process_list);
}
