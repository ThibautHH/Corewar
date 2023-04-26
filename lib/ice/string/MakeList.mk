##
## EPITECH PROJECT, 2023
## libice
## File description:
## MakeList.mk
##

DIR			+=	$(addprefix $(DIR_ICE), string/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_strcat.c	\
				ice_strcmp.c	\
				ice_strcpy.c	\
				ice_strdup.c	\
				ice_strlen.c	\
				ice_strncat.c	\
				ice_strncmp.c	\
				ice_strncpy.c	\
				ice_strndup.c	\
				ice_strnrev.c	\
				ice_strrev.c	\
				ice_strswap.c	\
				ice_strsplit.c	\
				ice_strstr.c	\
				ice_strchr.c	\
				ice_strtrim.c	\
				)
