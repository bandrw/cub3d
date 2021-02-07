/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 03:45:19 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/07 03:45:20 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				img_pixel_put(t_img *img_data, int x, int y, unsigned int color)
{
	char *dst;

	if (x >= img_data->width || x < 0 || y >= img_data->height || y < 0)
		return (1);
	dst = img_data->addr + (y * img_data->line_length + x *
							(img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	return (0);
}

unsigned int	img_get_pixel(t_img *img_data, int x, int y)
{
	char *dst;

	dst = img_data->addr + (y * img_data->line_length + x *
							(img_data->bits_per_pixel / 8));
	if (dst)
		return (*(unsigned int*)dst);
	return (0);
}

void			put_rectangle(t_img *img_data, t_rectangle *rectangle,
								int color)
{
	int start_x;
	int start_y;
	int i;
	int j;

	start_x = (int)rectangle->start.x;
	start_y = (int)rectangle->start.y;
	i = start_x;
	while (i < start_x + rectangle->width)
	{
		j = start_y;
		while (j < start_y + rectangle->height)
		{
			if (i >= 0 && j >= 0 && i < img_data->width && j < img_data->height)
				img_pixel_put(img_data, i, j, color);
			j++;
		}
		i++;
	}
}

static void		put_skybox(t_mlx *mlx_info)
{
	int				i;
	int				j;
	unsigned int	color;
	t_point			point;

	i = -1;
	while (++i < mlx_info->width)
	{
		j = -1;
		while (++j < mlx_info->height / 2)
		{
			point.x = -mlx_info->player.angle * mlx_info->skybox_texture.width /
				60.f + i * mlx_info->skybox_texture.width /
				(float)mlx_info->width;
			point.y = j * 2 * mlx_info->skybox_texture.height /
				(float)mlx_info->height;
			while (point.x < 0)
				point.x += mlx_info->skybox_texture.width;
			while (point.x > mlx_info->skybox_texture.width)
				point.x -= mlx_info->skybox_texture.width;
			color = img_get_pixel(&mlx_info->skybox_texture, point.x, point.y);
			img_pixel_put(&mlx_info->stage, i, j, color);
		}
	}
}

void			put_ceilling_and_floor(t_mlx *mlx_info)
{
	t_rectangle rectangle;

	put_skybox(mlx_info);
	rectangle.width = mlx_info->width;
	rectangle.height = mlx_info->height / 2;
	rectangle.start.x = 0;
	rectangle.start.y = (float)mlx_info->height / 2.f;
	put_rectangle(&mlx_info->stage, &rectangle, mlx_info->floor_color);
}
