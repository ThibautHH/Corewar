##
## EPITECH PROJECT, 2023
## corewar
## File description:
## Makefile
##

NAME		:=	asm

LIB			:=	../lib/

DIR_SRC		:=	src/

DIR			:=	$(DIR_SRC)
SRC			:=	$(addprefix $(DIR),\
				main.c				\
				asm.c				\
				)

DIR			+=	$(addprefix $(DIR_SRC), lexer/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				lexer.c				\
				token.c				\
				extract.c			\
				create_header.c		\
				destroy.c			\
				label.c				\
				operator.c			\
				)

DIR			+=	$(addprefix $(DIR_SRC), parser/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				parser.c			\
				add_argument.c		\
				label.c				\
				is_index.c			\
				has_coding_byte.c	\
				destroy.c			\
				)

DIR			+=	$(addprefix $(DIR_SRC), writer/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				writer.c			\
				get_filename.c		\
				)

DIR_BUILD	:=	../build/

ROOT_OBJ	:=	$(addprefix $(DIR_BUILD), obj/$(NAME)/)
DIR_OBJ		:=	$(addprefix $(ROOT_OBJ), $(DIR))
OBJ			:=	$(patsubst %.c, $(ROOT_OBJ)%.o, $(SRC))

UNIT_TEST	:=	../unit_test

RM			:=	rm -rf
MAKE		:=	make -sC$(LIB) -j

CC			:=	gcc
CFLAGS		:=	-I../include/ -Wall -Wextra
LDFLAGS		:=	-L$(LIB)
LDLIBS		:=	-lice

DEBUG		:=	-g
D_ROOT_OBJ	:=	$(addprefix $(DIR_BUILD), debug/obj/$(NAME)/)
D_OBJ		:=	$(patsubst %.c, $(D_ROOT_OBJ)%.o, $(SRC))
DIR_OBJ		+=	$(addprefix $(D_ROOT_OBJ), $(DIR))

all:				$(DIR_OBJ) lib $(NAME)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)\
	&& printf "\033[93m[CREATED]\033[0m %s\n" $(DIR_OBJ)\
	|| printf "\033[31m[ERROR]\033[0m %s\n" $(DIR_OBJ)

$(ROOT_OBJ)%.o:		%.c
	@$(CC) $(CFLAGS) -c $< -o $@\
	&& printf "\033[32m[OK]\033[0m %s\n" $<\
	|| printf "\033[31m[KO]\033[0m %s\n" $<

$(D_ROOT_OBJ)%.o:		%.c
	@$(CC) $(CFLAGS) -c $< -o $@\
	&& printf "\033[32m[OK]\033[0m %s\n" $<\
	|| printf "\033[31m[KO]\033[0m %s\n" $<

$(NAME):			$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)\
	&& printf "\033[32m[SUCCESS]\033[0m %s\n" $@\
	|| printf "\033[31m[ERROR]\033[0m %s\n" $@

lib:
	@$(MAKE)

lib_debug:
	@make -sC $(LIB) debug

debug:				CFLAGS += $(DEBUG)
debug:				OBJ := $(D_OBJ)
debug:				lib_debug $(DIR_OBJ) $(D_OBJ) $(NAME)

clean:
	@$(MAKE) $@
	@[ -d $(DIR_BUILD) ]\
	&& $(RM) $(DIR_BUILD)\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(DIR_BUILD) || true

fclean:				clean
	@$(MAKE) $@
	@[ -f $(NAME) ]\
	&& $(RM) $(NAME)\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(NAME) || true

re:					fclean all

.PHONY:				all debug clean fclean re $(NAME) $(ROOT_OBJ) $(D_ROOT_OBJ)

.SILENT:			all debug clean fclean re $(NAME) $(ROOT_OBJ) $(D_ROOT_OBJ)
