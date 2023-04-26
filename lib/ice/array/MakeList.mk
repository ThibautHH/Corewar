##
## EPITECH PROJECT, 2023
## libice
## File description:
## MakeList.mk
##

DIR			+=	$(addprefix $(DIR_ICE), array/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_array_len.c		\
				ice_free_array.c	\
				)
