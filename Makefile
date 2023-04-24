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

$(UNIT_TEST):
	@for i in $(SRC); do\
		$(MAKE) $$i $(UNIT_TEST);\
	done

debug:
	@for i in $(SRC); do\
		$(MAKE) $$i debug;\
	done

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
