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
	y_delta = mlx_info->player.position.y - (float)((int)mlx_info->player.position.y / (int)(mlx_info->height / mlx_info->map_height) * (int)((float)mlx_info->height / mlx_info->map_height));
	if (sinf(ft_to_radians(angle)) < 0)
		y_delta = ((float)mlx_info->height / mlx_info->map_height) - y_delta;
	x_delta = ft_absf((float)y_delta / tanf(ft_to_radians(angle)));
	if (cosf(ft_to_radians(angle)) < 0)
		x_delta = -x_delta;
	cast->length += ft_absf((float)y_delta / sinf(ft_to_radians(angle)));
	ray_x = mlx_info->player.position.x + x_delta;
	ray_y = mlx_info->player.position.y - (sinf(ft_to_radians(angle)) > 0 ? y_delta : -y_delta);
	x_delta = ((float)mlx_info->height / mlx_info->map_height) / ft_absf(tanf(ft_to_radians(angle)));
	if (cosf(ft_to_radians(angle)) < 0)
		x_delta = -x_delta;
	y_delta = sinf(ft_to_radians(angle)) > 0 ? ((float)mlx_info->height / mlx_info->map_height) : -((float)mlx_info->height / mlx_info->map_height);
	while (ray_y < (float)mlx_info->height && ray_x < (float)mlx_info->width && ray_y > 0 && ray_x > 0 &&
		mlx_info->map[(int)(mlx_info->map_height * ray_y / (float)mlx_info->height - (float)(sinf(ft_to_radians(angle)) > 0))][(int)(mlx_info->map_width * ray_x / (float)mlx_info->width)] != '1')
	{
		ray_x += x_delta;
		ray_y -= y_delta;
		cast->length += ((float)mlx_info->height / mlx_info->map_height) / ft_absf(sinf(ft_to_radians(angle)));
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
	x_delta = mlx_info->player.position.x - (float)((int)mlx_info->player.position.x / (int)((float)mlx_info->height / mlx_info->map_height) * (int)((float)mlx_info->height / mlx_info->map_height));
	if (cosf(ft_to_radians(angle)) > 0)
		x_delta = (int)((float)mlx_info->height / mlx_info->map_height) - x_delta;
	y_delta = ft_absf(x_delta * tanf(ft_to_radians(angle)));
	if (sinf(ft_to_radians(angle)) < 0)
		y_delta = -y_delta;
	cast->length += ft_absf(x_delta / cosf(ft_to_radians(angle)));
	ray_x = mlx_info->player.position.x + ((cosf(ft_to_radians(angle)) > 0) ? x_delta : -x_delta);
	ray_y = mlx_info->player.position.y - y_delta;
	y_delta = (int)((float)mlx_info->height / mlx_info->map_height) * ft_absf(tanf(ft_to_radians(angle)));
	if (sinf(ft_to_radians(angle)) < 0.f)
		y_delta = -y_delta;
	x_delta = cosf(ft_to_radians(angle)) > 0 ? ((float)mlx_info->height / mlx_info->map_height) : -((float)mlx_info->height / mlx_info->map_height);
	while (ray_y < (float)mlx_info->height && ray_x < (float)mlx_info->width && ray_y > 0 && ray_x > 0 &&
		   mlx_info->map[(int)(mlx_info->map_height * ray_y / (float)mlx_info->height)][(int)(mlx_info->map_width * ray_x / (float)mlx_info->width - (float)(cosf(ft_to_radians(angle)) < 0))] != '1')
	{
		ray_x += x_delta;
		ray_y -= y_delta;
		cast->length += ((float)mlx_info->height / mlx_info->map_height) / ft_absf(cosf(ft_to_radians(angle)));
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
