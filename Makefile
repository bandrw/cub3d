# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/05 14:19:32 by kfriese           #+#    #+#              #
#    Updated: 2020/12/05 14:19:34 by kfriese          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBFT_DIR = libft
LIBFT_NAME = $(LIBFT_DIR)/libft.a
HEADERS_DIR = includes
OBJ_DIR = obj
SRCS_DIR = srcs
HEADER_FILES = cub3d.h
HEADERS = $(addprefix $(HEADERS_DIR)/, $(HEADER_FILES))

FLAGS = -Wall -Wextra -Werror
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft -I$(LIBFT_DIR)/includes
LIBMLX_FLAGS = -I/usr/local/include -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

FILES = main.c

SRCS = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: build_libft $(NAME)

$(NAME): $(LIBFT_NAME) $(OBJ)
	gcc -o $(NAME) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) $(OBJ)

build_libft:
	@echo "==> Building libft <=="
	@make -C $(LIBFT_DIR)
	@echo "==>      Done      <==\n"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) -I$(HEADERS_DIR) -I$(LIBFT_DIR)/includes -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	/bin/rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	/bin/rm -f $(NAME)

re: fclean all