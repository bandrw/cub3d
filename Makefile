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

NAME = cub3D

LIBFT_DIR = libft
LIBFT_NAME = $(LIBFT_DIR)/libft.a
LIBMLX_DIR = minilibx
LIBMLX_NAME = $(LIBMLX_DIR)/libmlx.a

HEADERS_DIR = includes
OBJ_DIR = obj
SRCS_DIR = srcs
HEADER_FILES = cub3d.h
HEADERS = $(addprefix $(HEADERS_DIR)/, $(HEADER_FILES))

FLAGS = -Wall -Wextra# -Werror
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft -I$(LIBFT_DIR)/includes
LIBMLX_FLAGS = -L$(LIBMLX_DIR) -lmlx -I$(LIBMLX_DIR) -framework OpenGL -framework AppKit

FILES = main.c \
		mlx_put.c \
		is_moveable.c \
		is_arrow.c \
		new_map.c \
		player.c \
		ray_cast.c \
		ft_to_radians.c \
		parse_config.c \
		error_handle.c \
		sprite.c

SRCS = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: $(OBJ_DIR) build_libft build_libmlx build_cub3D $(NAME)
	@echo "\033[44m  ✔︎      Done      ✔︎  \033[0m\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT_NAME) $(LIBMLX_NAME) $(OBJ)
	gcc -o $(NAME) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) $(OBJ)

build_libft:
	@echo "\n\033[44m ⏤  Building libft ⏤  \033[0m"
	@make -C $(LIBFT_DIR)
	@echo "\033[44m  ✔︎      Done      ✔︎  \033[0m\n"

build_libmlx:
	@echo "\033[44m ⏤  Building libmlx ⏤  \033[0m"
	@make -C $(LIBMLX_DIR)
	@echo "\033[44m  ✔︎      Done       ✔︎  \033[0m\n"

build_cub3D:
	@echo "\033[44m ⏤  Building cub3D ⏤  \033[0m"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	gcc $(FLAGS) -I$(HEADERS_DIR) -I$(LIBFT_DIR)/includes -I$(LIBMLX_DIR) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBMLX_DIR)
	/bin/rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBMLX_DIR)
	/bin/rm -f $(NAME)

re: fclean all
