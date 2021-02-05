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

static float	get_angle_diff(float a1, float a2)
{
	if (cosf(to_rad(a2)) > 0 || cosf(to_rad(a1)) > 0)
		return (a2 - a1);
	if (a1 > 114.f && a2 < 0)
		return (a2 + 360.f - a1);
	if (a1 < -114.f && a2 > 0)
		return (a2 - (a1 + 360.f));
	return (a2 - a1);
}

static float	get_sprite_length(t_mlx *mlx_info, int index)
{
	return (sqrtf(powf((float)mlx_info->sprites[index].x_index * 50.f + 25.f -
			mlx_info->player.position.x, 2) +
			powf((float)mlx_info->sprites[index].y_index * 50.f + 25.f -
			mlx_info->player.position.y, 2)));
}

static void		draw_sprite(t_mlx *mlx_info, float length, float sprite, const float lengths[mlx_info->width])
{
	int				i;
	int				j;
	float			size;
	int				x_start;
	int				y_start;
	unsigned int	color;

	if (fabsf(get_angle_diff(mlx_info->player.angle, sprite)) > 66.f)
		return ;
	if (fabsf(cosf(to_rad(mlx_info->player.angle - sprite))) < 0.001f)
		return ;
	size = 40.f * (float)mlx_info->width / length;
	x_start = (int)((get_angle_diff(sprite, mlx_info->player.angle) + 33.f) / 66.f * (float)mlx_info->width - size / 2.f);
	if (size + x_start < 0 || x_start > mlx_info->width)
		return ;
	size /= cosf(to_rad(get_angle_diff(mlx_info->player.angle, sprite)));
	x_start = (int)((get_angle_diff(sprite, mlx_info->player.angle) + 33.f) / 66.f * (float)mlx_info->width - size / 2.f);
	y_start = mlx_info->height / 2 - (int)size / 2;
	i = -1;
	while ((float)++i < size)
	{
		if (i + x_start >= 0 && i + x_start < mlx_info->width &&
			length <= lengths[i + x_start])
		{
			j = -1;
			if (y_start < 0)
				j = size / 2 - mlx_info->height / 2;
			while ((float)++j < size && j + y_start < mlx_info->height)
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
	int			i;
	int			j;
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
