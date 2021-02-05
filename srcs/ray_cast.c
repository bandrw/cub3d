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

static void	ray_cast_horizontal(t_mlx *mlx_info, t_ray *cast, float angle)
{
	float	x_delta;
	float	y_delta;
	float	ray_x;
	float	ray_y;
	int		index_x;
	int		index_y;

	if (fabsf(sinf(to_rad(angle))) < 0.001f)
	{
		cast->length = -1.f;
		return ;
	}
	if (sinf(to_rad(angle)) < 0)
		cast->direction = North;
	else
		cast->direction = South;
	cast->length = 0.f;
	y_delta = fmodf(mlx_info->player.position.y, 50.f);
	if (sinf(to_rad(angle)) < 0)
		y_delta = 50.f - y_delta;
	x_delta = fabsf((float)y_delta / tanf(to_rad(angle)));
	if (cosf(to_rad(angle)) < 0)
		x_delta = -x_delta;
	cast->length += fabsf((float)y_delta / sinf(to_rad(angle)));
	ray_x = mlx_info->player.position.x + x_delta;
	ray_y = mlx_info->player.position.y - (sinf(to_rad(angle)) > 0 ? y_delta : -y_delta);
	x_delta = 50.f / fabsf(tanf(to_rad(angle)));
	if (cosf(to_rad(angle)) < 0)
		x_delta = -x_delta;
	y_delta = sinf(to_rad(angle)) > 0 ? 50.f : -50.f;
	index_x = (int)(ray_x / 50.f);
	index_y = (int)(ray_y / 50.f - (float)(sinf(to_rad(angle)) > 0));
	while (index_x >= 0 && index_y >= 0 && index_y < mlx_info->map_height && index_x < (int)ft_strlen(mlx_info->map[index_y])
			&& mlx_info->map[index_y][index_x] != '1')
	{
		ray_x += x_delta;
		ray_y -= y_delta;
		cast->length += 50.f / fabsf(sinf(to_rad(angle)));
		index_x = (int)(ray_x / 50.f);
		index_y = (int)(ray_y / 50.f - (float)(sinf(to_rad(angle)) > 0));
	}
	cast->end.x = ray_x;
	cast->end.y = ray_y;
}

static void	ray_cast_vertical(t_mlx *mlx_info, t_ray *cast, float angle)
{
	float	x_delta;
	float	y_delta;
	float	ray_x;
	float	ray_y;
	int		index_x;
	int		index_y;

	if (fabsf(cosf(to_rad(angle))) < 0.001f)
	{
		cast->length = -1.f;
		return ;
	}
	if (cosf(to_rad(angle)) > 0)
		cast->direction = West;
	else
		cast->direction = East;
	cast->length = 0.f;
	x_delta = fmodf(mlx_info->player.position.x, 50.f);
	if (cosf(to_rad(angle)) > 0)
		x_delta = 50.f - x_delta;
	y_delta = fabsf(x_delta * tanf(to_rad(angle)));
	if (sinf(to_rad(angle)) < 0)
		y_delta = -y_delta;
	cast->length += fabsf(x_delta / cosf(to_rad(angle)));
	ray_x = mlx_info->player.position.x + ((cosf(to_rad(angle)) > 0) ? x_delta : -x_delta);
	ray_y = mlx_info->player.position.y - y_delta;
	y_delta = 50.f * fabsf(tanf(to_rad(angle)));
	if (sinf(to_rad(angle)) < 0.f)
		y_delta = -y_delta;
	x_delta = cosf(to_rad(angle)) > 0 ? 50.f : -50.f;
	index_x = (int)(ray_x / 50.f - (float)(cosf(to_rad(angle)) < 0));
	index_y = (int)(ray_y / 50.f);
	while (index_x >= 0 && index_y >= 0 && index_y < mlx_info->map_height &&
			index_x < (int)ft_strlen(mlx_info->map[index_y]) &&
			mlx_info->map[index_y][index_x] != '1')
	{
		ray_x += x_delta;
		ray_y -= y_delta;
		cast->length += 50.f / fabsf(cosf(to_rad(angle)));
		index_x = (int)(ray_x / 50.f - (float)(cosf(to_rad(angle)) < 0));
		index_y = (int)(ray_y / 50.f);
	}
	cast->end.x = ray_x;
	cast->end.y = ray_y;
}

void		ray_cast(t_mlx *mlx_info, t_ray *cast, float angle)
{
	t_ray horizontal;
	t_ray vertical;

	ft_bzero(&horizontal, sizeof(t_ray));
	ft_bzero(&vertical, sizeof(t_ray));
	ray_cast_horizontal(mlx_info, &horizontal, angle);
	ray_cast_vertical(mlx_info, &vertical, angle);
	if (horizontal.length < 0 ||
		(vertical.length < horizontal.length && vertical.length >= 0))
	{
		cast->length = vertical.length;
		cast->end = vertical.end;
		cast->direction = vertical.direction;
	}
	else
	{
		cast->length = horizontal.length;
		cast->end = horizontal.end;
		cast->direction = horizontal.direction;
	}
}
