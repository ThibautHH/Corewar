##
## EPITECH PROJECT, 2023
## libice
## File description:
## MakeList.mk
##

DIR			+=	list/
SRC			+=	$(addprefix $(lastword $(DIR)),\
				list_add_node.c		\
				list_add.c			\
				list_create.c		\
				list_destroy.c		\
				list_destroy_node.c	\
				list_get.c			\
				list_pop.c			\
				list_pop_node.c		\
				list_remove.c		\
				list_remove_node.c	\
				list_sort.c			\
				)
