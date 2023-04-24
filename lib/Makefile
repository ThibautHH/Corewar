##
## EPITECH PROJECT, 2023
## libice
## File description:
## Makefile
##

NAME		:=	libice.a

DIR			:=
SRC			:=

DIR_ICE		:=	ice/

MK_INCLUDE	:=	$(addprefix $(DIR_ICE), $(addsuffix /MakeList.mk,\
				array		\
				int			\
				memory		\
				output		\
				printf		\
				string		\
				))

MK_INCLUDE	+=	$(addsuffix /MakeList.mk,\
				list		\
				)

include		$(MK_INCLUDE)

DIR_TEST	:=	../tests/
SRC_TEST	:=	$(addprefix $(DIR_TEST),\
				test_array.c		\
				test_int.c			\
				test_output.c		\
				test_printf.c		\
				test_string.c		\
				test_memory.c		\
				test_list.c			\
				)

DIR_BUILD	:=	../build/

ROOT_OBJ	:=	$(addprefix $(DIR_BUILD), obj/)
DIR_OBJ		:=	$(addprefix $(ROOT_OBJ), $(DIR))
OBJ			:=	$(patsubst %.c, $(ROOT_OBJ)%.o, $(SRC))

TEST_DIR	:=	$(addprefix $(DIR_BUILD), tests/)
UNIT_TEST	:=	unit_test

RM			:=	rm -rf

CC			:=	gcc
CLINKER		:=	ar rc
CFLAGS		:=	-I../include/ -Wall -Wextra

all:				$(DIR_OBJ) $(NAME)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)\
	&& printf "\033[93m[CREATED]\033[0m %s\n" $(DIR_OBJ)\
	|| printf "\033[31m[ERROR]\033[0m %s\n" $(DIR_OBJ)

$(ROOT_OBJ)%.o:		%.c
	@$(CC) $(CFLAGS) -c $< -o $@\
	&& printf "\033[32m[OK]\033[0m %s\n" $<\
	|| printf "\033[31m[KO]\033[0m %s\n" $<

$(NAME):			$(OBJ)
	@$(CLINKER) $@ $(OBJ)\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@\
	|| printf "\033[31m[ERROR]\033[0m %s\n" $@

$(UNIT_TEST):		CFLAGS += -lcriterion --coverage
$(UNIT_TEST):		fclean
	mkdir -p $(TEST_DIR)
	@$(CC) $(CFLAGS) $(SRC) $(SRC_TEST) -o $(TEST_DIR)$@\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@\
	|| printf "\033[31m[ERROR]\033[0m %s\n" $@

tests_run:			$(UNIT_TEST)
	@./$(TEST_DIR)$(UNIT_TEST)
	gcovr $(TEST_DIR) --exclude tests/

debug:				CFLAGS += -g
debug:				re

clean:
	@[ -d $(DIR_BUILD) ]\
	&& $(RM) $(DIR_BUILD)\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(DIR_BUILD) || true

fclean:				clean
	@[ -f $(NAME) ]\
 	&& $(RM) $(NAME)\
 	&& printf "\033[31m[DELETED]\033[0m %s\n" $(NAME) || true

re:					fclean all

.PHONY:				all clean fclean re
