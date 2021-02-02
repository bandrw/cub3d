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

static int	is_visible(float sprite, float player)
{
	if (sprite < player + 33.f && sprite > player - 33.f)
		return (1);
	if (player < 0)
		player += 360.f;
	if (sprite < 0)
		sprite += 360.f;
	return (sprite < player + 33.f && sprite > player - 33.f);
}

static int	get_x_start(int width, float sprite, float player)
{
	if (player < 180 && player > 114 && sprite < -114 && sprite > -180)
		return ((int)((player + 33.f - (sprite + 360)) / 66.f * (float)width));
	if (player < -114 && player > -180 && sprite < 180 && sprite > 114)
		return ((int)((player + 360.f + 33.f - sprite) / 66.f * (float)width));
	return ((int)((player + 33.f - sprite) / 66.f * (float)width));
}

float		get_sprite_length(t_mlx *mlx_info, int index)
{
	return (sqrtf(powf((float)mlx_info->sprites[index].x_index * 50.f - mlx_info->player.position.x, 2) +
			powf((float)mlx_info->sprites[index].y_index * 50.f - mlx_info->player.position.y, 2)));
}

static void	draw_sprite(t_mlx *mlx_info, float length, float sprite, const float lengths[mlx_info->width])
{
	int		i;
	int		j;
	float	size;
	int		x_start;
	int		y_start;

	x_start = get_x_start(mlx_info->width, sprite, mlx_info->player.angle);
	size = 30.f * (float)mlx_info->width / length;
	y_start = mlx_info->height / 2 - (int)size / 2;
	printf("\t[drawing] x_start: %d, size: %f\n", x_start, size);
	i = -1;
	while ((float)++i < size)
	{
		j = -1;
//		if (length < lengths[i + x_start])
//		{
			while ((float)++j < size && y_start + j < mlx_info->height && y_start + j >= 0)
			{
				img_pixel_put(&mlx_info->stage, i + x_start, j + y_start, 0xFF0000);
			}
//		}
	}
}

void		put_sprites(t_mlx *mlx_info, const float lengths[mlx_info->width])
{
	int		i;
	float	sprite;

	i = -1;
	while (++i < mlx_info->sprites_count)
	{
		sprite = to_deg(atan2f(mlx_info->player.position.y -
				(float)mlx_info->sprites[i].y_index * 50.f,
				(float)mlx_info->sprites[i].x_index * 50.f -
				mlx_info->player.position.x));
		printf("sprite: %f, player: %f\n", sprite, mlx_info->player.angle);
		if (is_visible(sprite, mlx_info->player.angle))
			draw_sprite(mlx_info, get_sprite_length(mlx_info, i), sprite, lengths);
	}
	printf("\n");
}
