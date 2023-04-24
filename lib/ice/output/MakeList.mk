##
## EPITECH PROJECT, 2023
## libice
## File description:
## MakeList.mk
##

DIR			+=	$(addprefix $(DIR_ICE), output/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_puts.c		\
				ice_dputs.c		\
				)
