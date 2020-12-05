# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 13:11:23 by kfriese           #+#    #+#              #
#    Updated: 2020/10/28 13:11:24 by kfriese          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
HEADERS_DIR = includes
OBJ_DIR = obj
SRCS_DIR = srcs
HEADER_FILES = libft.h get_next_line.h ft_printf.h
HEADERS = $(addprefix $(HEADERS_DIR)/, $(HEADER_FILES))

FILES = ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		get_next_line.c \
		ft_printf/ft_flags.c \
		ft_printf/ft_printf.c \
		ft_printf/ft_printf_c.c \
		ft_printf/ft_printf_d.c \
		ft_printf/ft_printf_p.c \
		ft_printf/ft_printf_s.c \
		ft_printf/ft_printf_u.c \
		ft_printf/ft_printf_x.c \
		ft_nbrlen.c \
		ft_putchar.c \
		ft_putnbr.c \
		ft_max.c \
		ft_putstr.c \
		ft_hexstr.c

SRCS = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/ft_printf
	gcc $(FLAGS) -I$(HEADERS_DIR) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
