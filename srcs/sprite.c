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
#include "../includes/cub3d.h"
#include "../libft/includes/libft.h"
// todo delete this "../shit"

t_sprite	*new_sprite(float x, float y, float length)
{
	t_sprite *sprite;

	sprite = (t_sprite*)malloc(sizeof(t_sprite));
	if (!sprite)
		exit(3);
	sprite->coordinate.x = x;
	sprite->coordinate.y = y;
	sprite->length = length;
	return (sprite);
}

static int	is_visible(t_mlx *mlx_info, t_sprite *sprite)
{
	return (1);
}

static void	draw_sprite(t_mlx *mlx_info, t_sprite *sprite, float lengths[mlx_info->width])
{
	int x_tmp;

	x_tmp = 0;
	while (x_tmp < mlx_info->width)
	{
		if (lengths[x_tmp] > sprite->length)
			//draw line
		x_tmp++;
	}
}

void		put_sprites(t_mlx *mlx_info, float lengths[mlx_info->width])
{
	t_list		*tmp;
	t_sprite	*sprite;

	tmp = mlx_info->sprites;
	while (tmp)
	{
		sprite = tmp->content;
		if (is_visible(mlx_info, sprite))
			draw_sprite(mlx_info, sprite, lengths);
		tmp = tmp->next;
	}
	ft_lstclear(&mlx_info->sprites, free);
}
