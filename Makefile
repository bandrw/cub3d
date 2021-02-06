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
LIBMLX_STATIC_NAME = $(LIBMLX_DIR)/static/libmlx.a
LIBMLX_DYNAMIC_NAME = $(LIBMLX_DIR)/dynamic/libmlx.dylib

HEADERS_DIR = includes
OBJ_DIR = obj
SRCS_DIR = srcs
HEADER_FILES = cub3d.h bmp.h hooks.h parse.h
HEADERS = $(addprefix $(HEADERS_DIR)/, $(HEADER_FILES))

FLAGS = -Wall -Wextra -Werror
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft -I$(LIBFT_DIR)/includes
LIBMLX_FLAGS = -L$(LIBMLX_DIR)/static -lmlx -I$(LIBMLX_DIR)/static -framework OpenGL -framework AppKit

FILES = main.c \
		mlx_put.c \
		player.c \
		ray_cast.c \
		math_utils.c \
		parse_config.c \
		error_handle.c \
		sprite.c \
		save_image.c \
		hooks.c \
		main_render.c \
		parse_map.c \
		parse_utils.c \
		parse_info.c

SRCS = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

BONUS_FILES = main_bonus.c \
		mlx_put.c \
		player.c \
		ray_cast.c \
		math_utils.c \
		parse_config.c \
		error_handle.c \
		sprite_bonus.c \
		save_image.c \
		hooks.c \
		main_render_bonus.c \
		parse_map.c \
		parse_utils.c \
		parse_info.c \
		to_dark_bonus.c

BONUS_HEADER_FILES = cub3d.h bmp.h hooks.h parse.h bonus.h
BONUS_HEADERS = $(addprefix $(HEADERS_DIR)/, $(BONUS_HEADER_FILES))
BONUS_SRCS = $(addprefix bonus/, $(FILES))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_FILES:.c=.o))

all: $(OBJ_DIR) build_libft build_libmlx build_cub3D $(NAME)
	@echo "\033[44m ✔︎      Done      ✔︎ \033[0m\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT_NAME) $(LIBMLX_STATIC_NAME) $(LIBMLX_DYNAMIC_NAME) $(OBJ)
	gcc -O3 -o $(NAME) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) $(OBJ) libmlx.dylib

build_libft:
	@echo "\n\033[44m ⏤  Building libft ⏤  \033[0m"
	@make -C $(LIBFT_DIR)
	@echo "\033[44m ✔︎      Done      ✔︎ \033[0m\n"

build_libmlx:
	@echo "\033[44m ⏤  Building libmlx ⏤  \033[0m"
	@make -C $(LIBMLX_DIR)/static
	@make -C $(LIBMLX_DIR)/dynamic && cp $(LIBMLX_DIR)/dynamic/libmlx.dylib .
	@echo "\033[44m ✔︎      Done       ✔︎ \033[0m\n"

build_cub3D:
	@echo "\033[44m ⏤  Building cub3D ⏤  \033[0m"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	gcc -O3 $(FLAGS) -I$(HEADERS_DIR) -I$(LIBFT_DIR)/includes -I$(LIBMLX_DIR) -c $< -o $@

bonus: $(OBJ_DIR) build_libft build_libmlx build_cub3D $(BONUS_OBJ)
	gcc -O3 -o $(NAME) $(LIBFT_FLAGS) $(LIBMLX_FLAGS) $(BONUS_OBJ) libmlx.dylib
	@echo "\033[44m ✔︎      Done      ✔︎ \033[0m\n"

$(OBJ_DIR)/%.o: bonus/%.c $(BONUS_HEADERS)
	gcc -O3 $(FLAGS) -I$(HEADERS_DIR) -I$(LIBFT_DIR)/includes -I$(LIBMLX_DIR) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBMLX_DIR)/static
	@make clean -C $(LIBMLX_DIR)/dynamic
	/bin/rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBMLX_DIR)/static
	@make fclean -C $(LIBMLX_DIR)/dynamic
	/bin/rm -f libmlx.dylib
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: bonus
