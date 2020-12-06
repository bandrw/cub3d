/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 14:09:59 by kfriese           #+#    #+#             */
/*   Updated: 2020/12/05 14:09:59 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		main_render(t_mlx *mlx_info)
{
	double x;
	double y;
	double tmp_angle;
	double c[mlx_info->width];

	put_square(mlx_info, mlx_info->player->position, 10);
	tmp_angle = mlx_info->player->angle - 30;
	for (int i = 0; i < mlx_info->width; i++)
	{
		c[i] = 0;
		while (c[i] < mlx_info->width)
		{
			x = mlx_info->player->position->x + c[i] * cos(tmp_angle * 3.14 / 180.0);
			y = mlx_info->player->position->y + c[i] * sin(tmp_angle * 3.14 / 180.0);
			if (x == 0 || y == 0 || mlx_info->width / (int)x == 0 || mlx_info->width / (int)y == 0)
				break;
			if (mlx_info->map[10 / (mlx_info->width / (int)x)][10 / (mlx_info->width / (int)y)] == '1')
				break;
			c[i] += 0.1;
		}
		tmp_angle += 60 / (double)mlx_info->width;
		int j = (int)c[i];
		while (j > 0)
		{
			mlx_pixel_put(mlx_info->init, mlx_info->window, i, (mlx_info->height - (int)c[i]) / 2 + j, 0xFFFFFF - (int)c[i]);
			j--;
		}
	}
}

static int		key_handle(int key, t_mlx *mlx_info)
{
	int step;

	step = 10;
	if (is_moveable(key) || is_arrow(key))
		mlx_clear_window(mlx_info->init, mlx_info->window);
	if (is_moveable(key))
		move(mlx_info, key, step);
	else if (is_arrow(key))
		change_direction(mlx_info, key);
	if (is_moveable(key) || is_arrow(key))
		main_render(mlx_info);
	return (0);
}

static t_player	*new_player(int width, int height)
{
	t_player *player;

	if ((player = (t_player*)malloc(sizeof(t_player))) == 0)
		return (0);
	if ((player->position = (t_point*)malloc(sizeof(t_point))) == 0)
	{
		free(player);
		return (0);
	}
	player->position->x = width / 2;
	player->position->y = height / 2;
	player->angle = 90;
	return (player);
}

static t_mlx	*new_mlx(int width, int height, char *title)
{
	t_mlx *mlx_info;

	if ((mlx_info = (t_mlx*)malloc(sizeof(t_mlx))) == 0)
		return (0);
	if ((mlx_info->player = new_player(width, height)) == 0)
	{
		free(mlx_info);
		return (0);
	}
	if (!(mlx_info->map = new_map()))
	{
		free(mlx_info->player);
		free(mlx_info);
		return (0);
	}
	mlx_info->init = mlx_init();
	mlx_info->height = height;
	mlx_info->width = width;
	mlx_info->window = mlx_new_window(mlx_info->init, width, height, title);
	return (mlx_info);
}

int				main(void)
{
	t_mlx *mlx_info;

	if (!(mlx_info = new_mlx(500, 500, "Cub 3D")))
		return (1);
	main_render(mlx_info);
	mlx_key_hook(mlx_info->window, &key_handle, mlx_info);
	mlx_loop(mlx_info->init);
	return (0);
}
