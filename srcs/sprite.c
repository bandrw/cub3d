/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 06:38:39 by kfriese           #+#    #+#             */
/*   Updated: 2021/01/10 06:38:39 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		get_x_start(int width, float sprite, float player)
{
	if (player < 180 && player > 114 && sprite < -114 && sprite > -180)
		return ((int)((player + 33.f - (sprite + 360)) / 66.f * (float)width));
	if (player < -114 && player > -180 && sprite < 180 && sprite > 114)
		return ((int)((player + 360.f + 33.f - sprite) / 66.f * (float)width));
	return ((int)((player + 33.f - sprite) / 66.f * (float)width));
}

static float	get_sprite_length(t_mlx *mlx_info, int index)
{
	return (sqrtf(powf((float)mlx_info->sprites[index].x_index * 50.f + 25.f - mlx_info->player.position.x, 2) +
			powf((float)mlx_info->sprites[index].y_index * 50.f + 25.f - mlx_info->player.position.y, 2)));
}

static void		draw_sprite(t_mlx *mlx_info, float length, float sprite, const float lengths[mlx_info->width])
{
	int				i;
	int				j;
	float			size;
	int				x_start;
	int				y_start;
	unsigned int	color;

	size = 30.f * (float)mlx_info->width / length;
	x_start = get_x_start(mlx_info->width, sprite, mlx_info->player.angle) - size / 2;
	y_start = mlx_info->height / 2 - (int)size / 2;
	i = -1;
	while ((float)++i < size)
	{
		j = -1;
		if (i + x_start >= 0 && i + x_start < mlx_info->width &&
			length <= lengths[i + x_start])
		{
			while ((float)++j < size && y_start + j < mlx_info->height && y_start + j >= 0)
			{
				color = img_get_pixel(&mlx_info->sprite_texture, i * (mlx_info->sprite_texture.width / size), j * (mlx_info->sprite_texture.height / size));
				if (color != 0xFF000000)
					img_pixel_put(&mlx_info->stage, i + x_start, j + y_start, color);
			}
		}
	}
}

static void		sort_sprites(t_mlx *mlx_info)
{
	int 		i;
	int 		j;
	t_sprite	tmp;

	i = 0;
	while (i < mlx_info->sprites_count)
	{
		j = i + 1;
		while (j < mlx_info->sprites_count)
		{
			if (mlx_info->sprites[i].length < mlx_info->sprites[j].length)
			{
				tmp = mlx_info->sprites[i];
				mlx_info->sprites[i].x_index = mlx_info->sprites[j].x_index;
				mlx_info->sprites[i].y_index = mlx_info->sprites[j].y_index;
				mlx_info->sprites[i].length = mlx_info->sprites[j].length;
				mlx_info->sprites[j].x_index = tmp.x_index;
				mlx_info->sprites[j].y_index = tmp.y_index;
				mlx_info->sprites[j].length = tmp.length;
			}
			j++;
		}
		i++;
	}
}

void			put_sprites(t_mlx *mlx_info, const float lengths[mlx_info->width])
{
	int		i;
	float	sprite;

	i = -1;
	while (++i < mlx_info->sprites_count)
		mlx_info->sprites[i].length = get_sprite_length(mlx_info, i);
	i = -1;
	sort_sprites(mlx_info);
	while (++i < mlx_info->sprites_count)
	{
		sprite = to_deg(atan2f(mlx_info->player.position.y -
				(float)mlx_info->sprites[i].y_index * 50.f - 25.f,
				(float)mlx_info->sprites[i].x_index * 50.f -
				mlx_info->player.position.x + 25.f));
		draw_sprite(mlx_info, mlx_info->sprites[i].length, sprite, lengths);
	}
}
