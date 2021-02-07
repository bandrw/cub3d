/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 09:55:25 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/07 09:55:26 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_crosshair(t_mlx *mlx_info)
{
	int				i;
	unsigned int	color;

	color = 0xFF0000;
	i = -1;
	while (++i < 10)
	{
		img_pixel_put(&mlx_info->stage, mlx_info->width / 2, mlx_info->height
						/ 2 - 3 - i, color);
		img_pixel_put(&mlx_info->stage, mlx_info->width / 2, mlx_info->height
						/ 2 + 3 + i, color);
		img_pixel_put(&mlx_info->stage, mlx_info->width / 2 - 3 - i,
						mlx_info->height / 2, color);
		img_pixel_put(&mlx_info->stage, mlx_info->width / 2 + 3 + i,
						mlx_info->height / 2, color);
	}
}

void		put_shooting_stuff(t_mlx *mlx_info)
{
	int				i;
	int				j;
	unsigned int	color;
	t_point			size;

	size.x = mlx_info->width * 4 / 9;
	size.y = (float)mlx_info->gun_texture.height /
			(float)mlx_info->gun_texture.width * size.x;
	i = -1;
	while (++i < size.x)
	{
		j = -1;
		while (++j < size.y)
		{
			color = img_get_pixel(&mlx_info->gun_texture,
						i * mlx_info->gun_texture.width / size.x,
						j * mlx_info->gun_texture.height / size.y);
			if (color != 0xFF000000)
				img_pixel_put(&mlx_info->stage, i + mlx_info->width - size.x,
				j + mlx_info->height - size.y, color);
		}
	}
	put_crosshair(mlx_info);
}

void		delete_sprite(t_mlx *mlx_info, int i)
{
	mlx_info->map[mlx_info->sprites[i].y_index]
			[mlx_info->sprites[i].x_index] = '0';
	mlx_info->sprites[i].x_index = -1;
}
