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

#include "../includes/cub3d.h"

static float	ray_cast_horizontal(t_mlx *mlx_info, float angle, t_img *tmp)
{
	float	distance;
	int		x_delta;
	int		y_delta;
	int		ray_x;
	int		ray_y;

	if (sinf(angle * 3.14f / 180.f) == 0)
		return (-1.f);
	distance = 0.f;
	y_delta = mlx_info->player.position.y - (int)mlx_info->player.position.y / 50 * 50;
	x_delta = ft_absf(50 / tanf(angle * 3.14f / 180.f));
	if (cosf(angle * 3.14f / 180.f) < 0)
		x_delta = -x_delta;
	distance += y_delta / sinf(angle * 3.14f / 180.f);
	ray_x = mlx_info->player.position.x + y_delta / tanf(angle * 3.14f / 180.f);
	ray_y = mlx_info->player.position.y - y_delta;
	while (ray_y < 500 && ray_x < 500 && ray_y > 0 && ray_x > 0 &&
		   mlx_info->map[10 * ray_y / mlx_info->height - (sinf(angle * 3.14f / 180.f) > 0)][10 * ray_x / mlx_info->width] != '1')
	{
		ray_x += x_delta;
		ray_y -= sinf(angle * 3.14f / 180.f) > 0 ? 50 : -50;
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

	distance = 0.f;
	x_delta = 50;
	if (cosf(angle * 3.14f / 180.f) < 0)
		x_delta = -x_delta;
	y_delta = ft_absf(50.f * tanf(angle * 3.14 / 180.f));
	ray_x = mlx_info->player.position.x;
	ray_y = mlx_info->player.position.y;
	while (ray_y < 500 && ray_x < 500 && ray_y > 0 && ray_x > 0 &&
			mlx_info->map[10 * ray_y / mlx_info->height][10 * ray_x / mlx_info->width - (cosf(angle * 3.14f / 180.f) < 0)] != '1')
	{
		ray_x += x_delta;
		ray_y -= sinf(angle * 3.14f / 180.f) > 0 ? y_delta : -y_delta;
		t_rectangle rectangle;
		rectangle.start.x = ray_x - 2;
		rectangle.start.y = ray_y - 2;
		rectangle.heigth = 4;
		rectangle.width = 4;
		if (rectangle.start.x < 498 && rectangle.start.y < 498 && rectangle.start.x > 0 && rectangle.start.y > 0)
			put_rectangle(tmp, &rectangle, 0xFF0000);
		if (cosf(angle * 3.14f / 180.f) == 0)
			return (-1);
		distance += 50.f / ft_absf(cosf(angle * 3.14f / 180.f));
		printf("%d %d\n", ray_x, ray_y);
	}
	printf("\n");
	return (distance);
}

float	ray_cast(t_mlx *mlx_info, float angle, t_img *tmp)
{
	float a;
	float b;

	a = ray_cast_horizontal(mlx_info, angle, tmp);
	b = ray_cast_vertical(mlx_info, angle, tmp);
	printf("%f : %f\n", a, b);
	if (a < 0 || b < a)
		return (b);
	return (a);
}
