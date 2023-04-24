##
## EPITECH PROJECT, 2023
## libice
## File description:
## MakeList.mk
##

DIR			+=	$(addprefix $(lastword $(DIR_ICE)), printf/private/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				handle_format.c			\
				get_argument.c			\
				add_buffer.c			\
                add_width.c				\
				ice_printf_char.c		\
				ice_printf_str.c		\
				ice_printf_percent.c	\
				ice_printf_int.c		\
				ice_printf_uint.c		\
				ice_printf_binary.c		\
				ice_printf_octal.c		\
				ice_printf_hexa.c		\
				ice_printf_hexa_upper.c	\
				ice_printf_ptr.c		\
				ice_printf_len.c		\
				ice_printf_float.c		\
				)