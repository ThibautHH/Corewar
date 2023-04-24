##
## EPITECH PROJECT, 2023
## libice
## File description:
## MakeList.mk
##

DIR			+=	$(addprefix $(DIR_ICE), int/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_atoi.c		\
				ice_itoa.c		\
				ice_utoa.c		\
				ice_btoa.c		\
				ice_ftoa.c		\
				ice_strtol.c	\
				ice_intlen.c	\
				)
