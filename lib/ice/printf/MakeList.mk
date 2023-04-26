##
## EPITECH PROJECT, 2023
## libice
## File description:
## MakeList.mk
##

include $(DIR_ICE)/printf/private/MakeList.mk

DIR			+=	$(addprefix $(DIR_ICE), printf/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_printf.c	\
				ice_dprintf.c	\
				ice_sprintf.c	\
				ice_snprintf.c	\
				ice_asprintf.c	\
				)
