##
## EPITECH PROJECT, 2023
## libice
## File description:
## MakeList.mk
##

DIR			+=	$(addprefix $(DIR_ICE), memory/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_realloc.c	\
				ice_calloc.c	\
				ice_memchr.c	\
				ice_memcmp.c	\
				ice_memcpy.c	\
				ice_memset.c	\
				)
