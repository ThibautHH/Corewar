##
## EPITECH PROJECT, 2023
## corewar
## File description:
## Makefile
##

SRC			:=	asm			\
				corewar

RM			:=	rm -rf
MAKE		:=	make -sC

all:
	@for i in $(SRC); do\
		$(MAKE) $$i;\
	done

debug:
	@for i in $(SRC); do\
		$(MAKE) $$i debug;\
	done

$(UNIT_TEST):
	@$(MAKE) ./lib/ $@

tests_run:
	@$(MAKE) ./lib/ $@
	@./tests/tester/tester_asm.sh

clean:
	@for i in $(SRC); do\
		$(MAKE) $$i clean;\
	done

fclean:
	@for i in $(SRC); do\
		$(MAKE) $$i fclean;\
	done

re:			fclean all

.PHONY:		all clean fclean re

.SILENT:	all clean fclean re
