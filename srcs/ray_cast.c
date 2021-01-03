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

static void write_rectangle(float ray_x, float ray_y, t_img *tmp, int color)
{
	t_rectangle rectangle;

	rectangle.start.x = ray_x - 2.f;
	rectangle.start.y = ray_y - 2.f;
	rectangle.heigth = 4;
	rectangle.width = 4;
	if (rectangle.start.x < 496 && rectangle.start.y < 496 && rectangle.start.x > 0 && rectangle.start.y > 0)
		put_rectangle(tmp, &rectangle, color);
}

static float	ray_cast_horizontal(t_mlx *mlx_info, float angle, t_img *tmp)
{
	float	distance;
	float	x_delta;
	float	y_delta;
	float	ray_x;
	float	ray_y;

	if (ft_absf(sinf(ft_to_radians(angle))) < 0.001f)
		return (-1.f);
	distance = 0.f;
	// смещение в пределах одной клетки
	y_delta = mlx_info->player.position.y - (float)((int)mlx_info->player.position.y / 50 * 50.f);
	if (sinf(ft_to_radians(angle)) < 0)
		y_delta = 50.f - y_delta;
	x_delta = ft_absf((float)y_delta / tanf(ft_to_radians(angle)));
	if (cosf(ft_to_radians(angle)) < 0)
		x_delta = -x_delta;
	distance += ft_absf((float)y_delta / sinf(ft_to_radians(angle)));
	ray_x = mlx_info->player.position.x + x_delta;
	ray_y = mlx_info->player.position.y - (sinf(ft_to_radians(angle)) > 0 ? y_delta : -y_delta);
//	write_rectangle(ray_x, ray_y, tmp, 0xFFFF00);
	// смещение пока не встретим стену
	x_delta = 50.f / ft_absf(tanf(ft_to_radians(angle)));
	if (cosf(ft_to_radians(angle)) < 0)
		x_delta = -x_delta;
	y_delta = sinf(ft_to_radians(angle)) > 0 ? 50.f : -50.f;
	while (ray_y < 500 && ray_x < 500 && ray_y > 0 && ray_x > 0 &&
		mlx_info->map[(int)(10.f * ray_y / (float)mlx_info->height - (float)(sinf(ft_to_radians(angle)) > 0))][(int)(10.f * ray_x / (float)mlx_info->width)] != '1')
	{
		ray_x += x_delta;
		ray_y -= y_delta;
//		write_rectangle(ray_x, ray_y, tmp, 0xFFFF00);
		distance += 50.f / ft_absf(sinf(ft_to_radians(angle)));
	}
	return (distance);
}

static float	ray_cast_vertical(t_mlx *mlx_info, float angle, t_img *tmp)
{
	float	distance;
	float	x_delta;
	float	y_delta;
	float	ray_x;
	float	ray_y;

	if (ft_absf(cosf(ft_to_radians(angle))) < 0.001f)
		return (-1.f);
	distance = 0.f;
	// смещение в пределах одной клетки
	x_delta = mlx_info->player.position.x - (float)((int)mlx_info->player.position.x / 50 * 50);
	if (cosf(ft_to_radians(angle)) > 0)
		x_delta = 50 - x_delta;
	y_delta = ft_absf(x_delta * tanf(ft_to_radians(angle)));
	if (sinf(ft_to_radians(angle)) < 0)
		y_delta = -y_delta;
	distance += ft_absf(x_delta / cosf(ft_to_radians(angle)));
	ray_x = mlx_info->player.position.x + ((cosf(ft_to_radians(angle)) > 0) ? x_delta : -x_delta);
	ray_y = mlx_info->player.position.y - y_delta;
//	write_rectangle(ray_x, ray_y, tmp, 0xFF0000);
	// смещение пока не встретим стену
	y_delta = 50 * ft_absf(tanf(angle * 3.14f / 180.f));
	if (sinf(ft_to_radians(angle)) < 0)
		y_delta = -y_delta;
	x_delta = cosf(ft_to_radians(angle)) > 0 ? 50 : -50;
	while (ray_y < 500 && ray_x < 500 && ray_y > 0 && ray_x > 0 &&
		   mlx_info->map[(int)(10.f * ray_y / (float)mlx_info->height)][(int)(10.f * ray_x / (float)mlx_info->width - (float)(cosf(ft_to_radians(angle)) < 0))] != '1')
	{
		ray_x += x_delta;
		ray_y -= y_delta;
//		write_rectangle(ray_x, ray_y, tmp, 0xFF0000);
		distance += 50.f / ft_absf(cosf(ft_to_radians(angle)));
	}
	return (distance);
}

float	ray_cast(t_mlx *mlx_info, float angle, t_img *tmp)
{
	float a;
	float b;

	a = ray_cast_horizontal(mlx_info, angle, tmp);
	b = ray_cast_vertical(mlx_info, angle, tmp);
	if (a < 0 || (b < a && b >= 0))
		return (b);
	return (a);
}
