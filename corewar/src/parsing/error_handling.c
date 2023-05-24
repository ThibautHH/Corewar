/*
** EPITECH PROJECT, 2023
** corewar
** File description:
** error_handling
*/

#include <stdio.h>
#include "ice/string.h"
#include "corewar/corewar.h"

static const char used_number[] = "Error: number used several times\n";

void is_champ_number_already_used(champion_t *champ)
{
    for (champion_t *other = TAILQ_NEXT(champ, entries); (other);
        (other = TAILQ_NEXT(other, entries)))
        if (other->number == champ->number) {
            fwrite(used_number, sizeof(used_number), 1, stderr);
            exit(84);
        }
}
