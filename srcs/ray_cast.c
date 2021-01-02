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

static void write_rectangle(int ray_x, int ray_y, t_img *tmp)
{
	t_rectangle rectangle;

	rectangle.start.x = (float)ray_x - 2;
	rectangle.start.y = (float)ray_y - 2;
	rectangle.heigth = 4;
	rectangle.width = 4;
	if (rectangle.start.x < 496 && rectangle.start.y < 496 && rectangle.start.x > 0 && rectangle.start.y > 0)
		put_rectangle(tmp, &rectangle, 0xFF0000);
}

static float	ray_cast_horizontal(t_mlx *mlx_info, float angle, t_img *tmp)
{
	float	distance;
	int		x_delta;
	int		y_delta;
	int		ray_x;
	int		ray_y;

	if (ft_absf(sinf(angle * 3.14f / 180.f)) < 0.001f)
		return (-1.f);
	distance = 0.f;
	// смещение в пределах одной клетки
	y_delta = (int)mlx_info->player.position.y - (int)mlx_info->player.position.y / 50 * 50;
	if (sinf(angle * 3.14f / 180.f) < 0)
		y_delta = 50 - y_delta;
	x_delta = (int)ft_absf((float)y_delta / tanf(angle * 3.14f / 180.f));
	if (cosf(angle * 3.14f / 180.f) < 0)
		x_delta = -x_delta;
	distance += ft_absf((float)y_delta / sinf(angle * 3.14f / 180.f));
	ray_x = (int)mlx_info->player.position.x + x_delta;
	ray_y = (int)mlx_info->player.position.y - (sinf(angle * 3.14f / 180.f) > 0 ? y_delta : -y_delta);
	write_rectangle(ray_x, ray_y, tmp);
	// смещение пока не встретим стену
	x_delta = (int)(50 / ft_absf(tanf(angle * 3.14f / 180.f)));
	if (cosf(angle * 3.14f / 180.f) < 0)
		x_delta = -x_delta;
	y_delta = sinf(angle * 3.14f / 180.f) > 0 ? 50 : -50;
	while (ray_y < 500 && ray_x < 500 && ray_y > 0 && ray_x > 0 &&
		mlx_info->map[10 * ray_y / mlx_info->height - (sinf(angle * 3.14f / 180.f) > 0)][10 * ray_x / mlx_info->width] != '1')
	{
		ray_x += x_delta;
		ray_y -= y_delta;
		write_rectangle(ray_x, ray_y, tmp);
		distance += 50.f / ft_absf(sinf(angle * 3.14f / 180.f));
	}
	return (distance);
}

static float	ray_cast_vertical(t_mlx *mlx_info, float angle, t_img *tmp)
{
	float	distance;
	int		x_delta;
	int		y_delta;
	int		ray_x;
	int		ray_y;

	if (ft_absf(cosf(angle * 3.14f / 180.f)) < 0.001f)
		return (-1.f);
	distance = 0.f;
	// смещение в пределах одной клетки
	x_delta = (int)mlx_info->player.position.x - (int)mlx_info->player.position.x / 50 * 50;
	if (cosf(angle * 3.14f / 180.f) > 0)
		x_delta = 50 - x_delta;
	y_delta = (int)ft_absf((float)x_delta * tanf(angle * 3.14f / 180.f));
	if (sinf(angle * 3.14f / 180.f) < 0)
		y_delta = -y_delta;
	distance += ft_absf((float)x_delta / cosf(angle * 3.14f / 180.f));
	ray_x = (int)mlx_info->player.position.x + ((cosf(angle * 3.14f / 180.f) > 0) ? x_delta : -x_delta);
	ray_y = (int)mlx_info->player.position.y - y_delta;
	write_rectangle(ray_x, ray_y, tmp);
	// смещение пока не встретим стену
	y_delta = (int)(50 * ft_absf(tanf(angle * 3.14f / 180.f)));
	if (sinf(angle * 3.14f / 180.f) < 0)
		y_delta = -y_delta;
	x_delta = cosf(angle * 3.14f / 180.f) > 0 ? 50 : -50;
	while (ray_y < 500 && ray_x < 500 && ray_y > 0 && ray_x > 0 &&
		   mlx_info->map[10 * ray_y / mlx_info->height][10 * ray_x / mlx_info->width - (cosf(angle * 3.14f / 180.f) < 0)] != '1')
	{
		ray_x += x_delta;
		ray_y -= y_delta;
		write_rectangle(ray_x, ray_y, tmp);
		distance += 50.f / ft_absf(cosf(angle * 3.14f / 180.f));
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
