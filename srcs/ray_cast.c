/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 04:47:32 by kfriese           #+#    #+#             */
/*   Updated: 2020/12/31 04:47:34 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../includes/cub3d.h"

static void	ray_cast_horizontal(t_mlx *mlx_info, t_ray *cast, float angle)
{
	float	x_delta;
	float	y_delta;
	float	ray_x;
	float	ray_y;
	int		index_x;
	int		index_y;

	if (ft_absf(sinf(ft_to_radians(angle))) < 0.001f)
	{
		cast->length = -1.f;
		return ;
	}
	cast->length = 0.f;
	cast->sprites = 0;
	y_delta = mlx_info->player.position.y - (float)((int)mlx_info->player.position.y / 50 * 50);
	if (sinf(ft_to_radians(angle)) < 0)
		y_delta = 50.f - y_delta;
	x_delta = ft_absf((float)y_delta / tanf(ft_to_radians(angle)));
	if (cosf(ft_to_radians(angle)) < 0)
		x_delta = -x_delta;
	cast->length += ft_absf((float)y_delta / sinf(ft_to_radians(angle)));
	ray_x = mlx_info->player.position.x + x_delta;
	ray_y = mlx_info->player.position.y - (sinf(ft_to_radians(angle)) > 0 ? y_delta : -y_delta);
	x_delta = 50.f / ft_absf(tanf(ft_to_radians(angle)));
	if (cosf(ft_to_radians(angle)) < 0)
		x_delta = -x_delta;
	y_delta = sinf(ft_to_radians(angle)) > 0 ? 50.f : -50.f;
	index_x = (int)(ray_x / 50.f);
	index_y = (int)(ray_y / 50.f - (float)(sinf(ft_to_radians(angle)) > 0));
	while (index_x >= 0 && index_y >= 0 && index_y < mlx_info->map_height && index_x < (int)ft_strlen(mlx_info->map[index_y])
			&& mlx_info->map[index_y][index_x] != '1')
	{
		if (mlx_info->map[index_y][index_x] == '2')
			ft_lstadd_front(&cast->sprites, ft_lstnew((int)cast->length));
		ray_x += x_delta;
		ray_y -= y_delta;
		cast->length += 50.f / ft_absf(sinf(ft_to_radians(angle)));
		index_x = (int)(ray_x / 50.f);
		index_y = (int)(ray_y / 50.f - (float)(sinf(ft_to_radians(angle)) > 0));
	}
	cast->end.x = ray_x;
	cast->end.y = ray_y;
	if (sinf(ft_to_radians(angle)) < 0)
		cast->direction = North;
	else
		cast->direction = South;
}

static void	ray_cast_vertical(t_mlx *mlx_info, t_ray *cast, float angle)
{
	float	x_delta;
	float	y_delta;
	float	ray_x;
	float	ray_y;
	int		index_x;
	int		index_y;

	if (ft_absf(cosf(ft_to_radians(angle))) < 0.001f)
	{
		cast->length = -1.f;
		return ;
	}
	cast->length = 0.f;
	cast->sprites = 0;
	x_delta = mlx_info->player.position.x - (float)((int)mlx_info->player.position.x / 50 * 50);
	if (cosf(ft_to_radians(angle)) > 0)
		x_delta = 50.f - x_delta;
	y_delta = ft_absf(x_delta * tanf(ft_to_radians(angle)));
	if (sinf(ft_to_radians(angle)) < 0)
		y_delta = -y_delta;
	cast->length += ft_absf(x_delta / cosf(ft_to_radians(angle)));
	ray_x = mlx_info->player.position.x + ((cosf(ft_to_radians(angle)) > 0) ? x_delta : -x_delta);
	ray_y = mlx_info->player.position.y - y_delta;
	y_delta = 50.f * ft_absf(tanf(ft_to_radians(angle)));
	if (sinf(ft_to_radians(angle)) < 0.f)
		y_delta = -y_delta;
	x_delta = cosf(ft_to_radians(angle)) > 0 ? 50.f : -50.f;
	index_x = (int)(ray_x / 50.f - (float)(cosf(ft_to_radians(angle)) < 0));
	index_y = (int)(ray_y / 50.f);
	while (index_x >= 0 && index_y >= 0 && index_y < mlx_info->map_height && index_x < (int)ft_strlen(mlx_info->map[index_y])
		   && mlx_info->map[index_y][index_x] != '1')
	{
		if (mlx_info->map[index_y][index_x] == '2')
			ft_lstadd_front(&cast->sprites, ft_lstnew((int)cast->length));
		ray_x += x_delta;
		ray_y -= y_delta;
		cast->length += 50.f / ft_absf(cosf(ft_to_radians(angle)));
		index_x = (int)(ray_x / 50.f - (float)(cosf(ft_to_radians(angle)) < 0));
		index_y = (int)(ray_y / 50.f);
	}
	cast->end.x = ray_x;
	cast->end.y = ray_y;
	if (cosf(ft_to_radians(angle)) > 0)
		cast->direction = West;
	else
		cast->direction = East;
}

void	ray_cast(t_mlx *mlx_info, t_ray *cast, float angle)
{
	t_ray horizontal;
	t_ray vertical;

	ray_cast_horizontal(mlx_info, &horizontal, angle);
	ray_cast_vertical(mlx_info, &vertical, angle);
	if (horizontal.length < 0 || (vertical.length < horizontal.length && vertical.length >= 0))
	{
		cast->sprites = vertical.sprites;
		cast->length = vertical.length;
		cast->end = vertical.end;
		cast->direction = vertical.direction;
//		ft_lstclear(&horizontal.sprites, 0);
	}
	else
	{
		cast->sprites = horizontal.sprites;
		cast->length = horizontal.length;
		cast->end = horizontal.end;
		cast->direction = horizontal.direction;
//		ft_lstclear(&vertical.sprites, 0);
	}
}
