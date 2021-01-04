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

	if (ft_absf(sinf(ft_to_radians(angle))) < 0.001f)
	{
		cast->length = -1.f;
		return ;
	}
	cast->length = 0.f;
	y_delta = mlx_info->player.position.y - (float)((int)mlx_info->player.position.y / 50 * 50.f);
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
	while (ray_y < 500 && ray_x < 500 && ray_y > 0 && ray_x > 0 &&
		mlx_info->map[(int)(10.f * ray_y / (float)mlx_info->height - (float)(sinf(ft_to_radians(angle)) > 0))][(int)(10.f * ray_x / (float)mlx_info->width)] != '1')
	{
		ray_x += x_delta;
		ray_y -= y_delta;
		cast->length += 50.f / ft_absf(sinf(ft_to_radians(angle)));
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

	if (ft_absf(cosf(ft_to_radians(angle))) < 0.001f)
	{
		cast->length = -1.f;
		return ;
	}
	cast->length = 0.f;
	x_delta = mlx_info->player.position.x - (float)((int)mlx_info->player.position.x / 50 * 50);
	if (cosf(ft_to_radians(angle)) > 0)
		x_delta = 50 - x_delta;
	y_delta = ft_absf(x_delta * tanf(ft_to_radians(angle)));
	if (sinf(ft_to_radians(angle)) < 0)
		y_delta = -y_delta;
	cast->length += ft_absf(x_delta / cosf(ft_to_radians(angle)));
	ray_x = mlx_info->player.position.x + ((cosf(ft_to_radians(angle)) > 0) ? x_delta : -x_delta);
	ray_y = mlx_info->player.position.y - y_delta;
	y_delta = 50 * ft_absf(tanf(angle * 3.14f / 180.f));
	if (sinf(ft_to_radians(angle)) < 0.f)
		y_delta = -y_delta;
	x_delta = cosf(ft_to_radians(angle)) > 0 ? 50 : -50;
	while (ray_y < 500 && ray_x < 500 && ray_y > 0 && ray_x > 0 &&
		   mlx_info->map[(int)(10.f * ray_y / (float)mlx_info->height)][(int)(10.f * ray_x / (float)mlx_info->width - (float)(cosf(ft_to_radians(angle)) < 0))] != '1')
	{
		ray_x += x_delta;
		ray_y -= y_delta;
		cast->length += 50.f / ft_absf(cosf(ft_to_radians(angle)));
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
	t_ray a;
	t_ray b;

	ray_cast_horizontal(mlx_info, &a, angle);
	ray_cast_vertical(mlx_info, &b, angle);
	if (a.length < 0 || (b.length < a.length && b.length >= 0))
	{
		cast->length = b.length;
		cast->end = b.end;
		cast->direction = b.direction;
	}
	else
	{
		cast->length = a.length;
		cast->end = a.end;
		cast->direction = a.direction;
	}
}
