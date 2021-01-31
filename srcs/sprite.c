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

void		sprite_add_xtmp(void *sprite, void *data)
{
	int			*x_tmp;
	t_sprite	*tmp;

	tmp = sprite;
	x_tmp = data;
	tmp->x_start += *x_tmp;
}

float		get_sprite_length(t_mlx *mlx_info, float x, float y)
{
	return (sqrtf((x - mlx_info->player.position.x) *
		(x - mlx_info->player.position.x) + (y - mlx_info->player.position.y) *
		(y - mlx_info->player.position.y)));
}

t_sprite	*new_sprite(float x, float y, float length, int is_vertical)
{
	t_sprite *sprite;

	sprite = (t_sprite*)malloc(sizeof(t_sprite));
	if (!sprite)
		exit(3);
	sprite->coordinate.x = x;
	sprite->coordinate.y = y;
	sprite->length = length;
	sprite->x_start = 0;
//	if (is_vertical)
//		sprite->x_start = (int)-(7 * sinf(ft_to_radians(45)) * (y - (int)y / 50 * 50));
//	else
//		sprite->x_start = (int)-(sqrtf(2) * 25 + 7 * sinf(ft_to_radians(45)) * (x - (int)x / 50 * 50));
	return (sprite);
}

void		put_sprites(t_mlx *mlx_info, t_list *sprites,
						const float lengths[mlx_info->width])
{
	t_sprite		*sprite;
	float			size;
	int				i;
	int				j;
	int				y;
	unsigned int	color;

	while (sprites)
	{
		sprite = sprites->content;
		size = 30.f * (float)mlx_info->width / sprite->length;
		sprite->x_start += (int)(size / 3.f);
		i = 0;
		y = mlx_info->height / 2 - (int)size / 2;
		while (i < (int)size)
		{
			if (sprite->x_start + i >= 0 &&
				sprite->x_start + i < mlx_info->width &&
				sprite->length < lengths[sprite->x_start + i])
			{
				j = 0;
				while (j < (int)size && y + j < mlx_info->height)
				{
					color = img_get_pixel(&mlx_info->sprite_texture, i * (mlx_info->sprite_texture.width / size), j * (mlx_info->sprite_texture.height / size));
					if (color != 0xFF000000)
						img_pixel_put(&mlx_info->stage, sprite->x_start + i, y + j, color);
					j++;
				}
			}
			i++;
		}
		sprites = sprites->next;
	}
}
