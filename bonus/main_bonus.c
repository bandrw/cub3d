/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:21:43 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/06 12:21:43 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hooks.h"

int				close_app(t_mlx *mlx_info)
{
	int i;

	mlx_destroy_image(mlx_info->init, mlx_info->stage.img);
	mlx_destroy_image(mlx_info->init, mlx_info->sprite_texture.img);
	mlx_destroy_image(mlx_info->init, mlx_info->east_texture.img);
	mlx_destroy_image(mlx_info->init, mlx_info->west_texture.img);
	mlx_destroy_image(mlx_info->init, mlx_info->south_texture.img);
	mlx_destroy_image(mlx_info->init, mlx_info->north_texture.img);
	mlx_destroy_window(mlx_info->init, mlx_info->window);
	i = 0;
	while (i < mlx_info->map_height)
	{
		free(mlx_info->map[i]);
		i++;
	}
	free(mlx_info->map);
	exit(0);
}

void			new_mlx(t_mlx *mlx_info, char *file, char *title, void *out)
{
	ft_bzero(mlx_info, sizeof(*mlx_info));
	if ((mlx_info->init = mlx_init()) == 0)
		throw_error("mlx init");
	mlx_info->window = out;
	parse_config(mlx_info, file);
	if (out)
	{
		if ((mlx_info->window = mlx_new_window(mlx_info->init, mlx_info->width,
											   mlx_info->height, title)) == 0)
			throw_error("mlx window");
	}
	mlx_info->stage.width = mlx_info->width;
	mlx_info->stage.height = mlx_info->height;
	mlx_info->stage.img = mlx_new_image(mlx_info->init, mlx_info->width,
										mlx_info->height);
	mlx_info->stage.addr = mlx_get_data_addr(mlx_info->stage.img,
											 &mlx_info->stage.bits_per_pixel, &mlx_info->stage.line_length,
											 &mlx_info->stage.endian);
}

static void		check_arguments(int argc, char **argv)
{
	char *p;

	if (argc == 2 || argc == 3)
	{
		p = ft_strrchr(argv[1], '.');
		if (!p || ft_strncmp(p, ".cub", 5) ||
			(argc == 3 && ft_strncmp(argv[2], "--save", 7) != 0))
			throw_error("Invalid arguments");
	}
	else
		usage_error(argv[0]);
}

int				main(int argc, char **argv)
{
	t_mlx mlx_info;

	check_arguments(argc, argv);
	if (argc == 2)
	{
		new_mlx(&mlx_info, argv[1], "Kfriese's Cub 3D", (void*)1);
		mlx_mouse_move(mlx_info.window, mlx_info.width / 2,
					   mlx_info.height / 2);
		mlx_hook(mlx_info.window, 2, 1L << 1, key_press, &mlx_info);
		mlx_hook(mlx_info.window, 3, 0, key_release, &mlx_info);
		mlx_hook(mlx_info.window, 6, 0, mouse_movement, &mlx_info);
		mlx_hook(mlx_info.window, 17, 1L << 17, close_app, &mlx_info);
		mlx_loop_hook(mlx_info.init, key_handle, &mlx_info);
		mlx_loop(mlx_info.init);
	}
	else if (argc == 3)
	{
		new_mlx(&mlx_info, argv[1], "Kfriese's Cub 3D", 0);
		save_image(&mlx_info, "out.bmp");
	}
	return (0);
}

