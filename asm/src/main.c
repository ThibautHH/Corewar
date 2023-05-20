/*
** EPITECH PROJECT, 2022
** Corewar/asm
** File description:
** Program entry point
*/

#include "asm.h"

const char *USAGE = "USAGE\n"
    "\t%s file_name[.s]\n"
    "DESCRIPTION\n"
    "\tfile_name\tfile in assembly language to be converted into file_name.cor, an\n"
    "\t\t\texecutable in the Virtual Machine.\n";

void __attribute__((noreturn)) quit(asm_t *ctx, int status)
{
    if (F(IN))
        fclose(F(IN));
    if (F(OUT))
        fclose(F(OUT));
    if (BUFFER)
        free(BUFFER);
    exit(status);
}

int main(int argc, char **argv)
{
    asm_t ctx = {.cmd = *argv, .file_name = argv[1], .line = 1, .col = 1,
        .header = {.magic = ENDIAN(COREWAR_EXEC_MAGIC)}};

    if (argc != 2 || !argv[1] || !*(argv[1])) {
        ice_dprintf(STDERR_FILENO, USAGE, *argv);
        return 84;
    }
    if (*(argv[1]) == '-' && argv[1][1] == 'h' && !argv[1][2]) {
        ice_dprintf(STDERR_FILENO, USAGE, *argv);
        return 0;
    }
    if (!open_binaries(&ctx, argv[1]))
        return 84;
    compile(&ctx);
    quit(&ctx, 0);
}
