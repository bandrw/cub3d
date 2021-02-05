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

static void	horizontal_action(t_mlx *mlx_info, t_ray *cast, float angle,
								t_pointf *ray)
{
	t_point		index;
	t_pointf	delta;

	delta.x = 50.f / fabsf(tanf(to_rad(angle)));
	if (cosf(to_rad(angle)) < 0)
		delta.x = -delta.x;
	delta.y = sinf(to_rad(angle)) > 0 ? 50.f : -50.f;
	index.x = (int)(ray->x / 50.f);
	index.y = (int)(ray->y / 50.f - (float)(sinf(to_rad(angle)) > 0));
	while (index.x >= 0 && index.y >= 0 && index.y < mlx_info->map_height &&
			index.x < (int)ft_strlen(mlx_info->map[index.y])
			&& mlx_info->map[index.y][index.x] != '1')
	{
		ray->x += delta.x;
		ray->y -= delta.y;
		cast->length += 50.f / fabsf(sinf(to_rad(angle)));
		index.x = (int)(ray->x / 50.f);
		index.y = (int)(ray->y / 50.f - (float)(sinf(to_rad(angle)) > 0));
	}
	cast->end.x = ray->x;
	cast->end.y = ray->y;
}

static int	ray_cast_horizontal(t_mlx *mlx_info, t_ray *cast, float angle)
{
	t_pointf delta;
	t_pointf ray;

	if (fabsf(sinf(to_rad(angle))) < 0.001f)
		return (-1);
	cast->direction = South;
	if (sinf(to_rad(angle)) < 0)
		cast->direction = North;
	delta.y = fmodf(mlx_info->player.position.y, 50.f);
	if (sinf(to_rad(angle)) < 0)
		delta.y = 50.f - delta.y;
	delta.x = fabsf((float)delta.y / tanf(to_rad(angle)));
	if (cosf(to_rad(angle)) < 0)
		delta.x = -delta.x;
	cast->length += fabsf((float)delta.y / sinf(to_rad(angle)));
	ray.x = mlx_info->player.position.x + delta.x;
	ray.y = mlx_info->player.position.y;
	if (sinf(to_rad(angle)) > 0)
		ray.y -= delta.y;
	else
		ray.y += delta.y;
	horizontal_action(mlx_info, cast, angle, &ray);
	return (0);
}

static void	vertical_action(t_mlx *mlx_info, t_ray *cast, float angle,
								t_pointf *ray)
{
	t_point		index;
	t_pointf	delta;

	delta.y = 50.f * fabsf(tanf(to_rad(angle)));
	if (sinf(to_rad(angle)) < 0.f)
		delta.y = -delta.y;
	delta.x = -50.f;
	if (cosf(to_rad(angle)) > 0)
		delta.x = 50.f;
	index.x = (int)(ray->x / 50.f - (float)(cosf(to_rad(angle)) < 0));
	index.y = (int)(ray->y / 50.f);
	while (index.x >= 0 && index.y >= 0 && index.y < mlx_info->map_height &&
			index.x < (int)ft_strlen(mlx_info->map[index.y]) &&
			mlx_info->map[index.y][index.x] != '1')
	{
		ray->x += delta.x;
		ray->y -= delta.y;
		cast->length += 50.f / fabsf(cosf(to_rad(angle)));
		index.x = (int)(ray->x / 50.f - (float)(cosf(to_rad(angle)) < 0));
		index.y = (int)(ray->y / 50.f);
	}
	cast->end.x = ray->x;
	cast->end.y = ray->y;
}

static int	ray_cast_vertical(t_mlx *mlx_info, t_ray *cast, float angle)
{
	t_pointf delta;
	t_pointf ray;

	if (fabsf(cosf(to_rad(angle))) < 0.001f)
		return (-1);
	cast->direction = East;
	if (cosf(to_rad(angle)) > 0)
		cast->direction = West;
	delta.x = fmodf(mlx_info->player.position.x, 50.f);
	if (cosf(to_rad(angle)) > 0)
		delta.x = 50.f - delta.x;
	delta.y = fabsf(delta.x * tanf(to_rad(angle)));
	if (sinf(to_rad(angle)) < 0)
		delta.y = -delta.y;
	cast->length += fabsf(delta.x / cosf(to_rad(angle)));
	ray.x = mlx_info->player.position.x;
	if (cosf(to_rad(angle)) > 0)
		ray.x += delta.x;
	else
		ray.x -= delta.x;
	ray.y = mlx_info->player.position.y - delta.y;
	vertical_action(mlx_info, cast, angle, &ray);
	return (0);
}

void		ray_cast(t_mlx *mlx_info, t_ray *cast, float angle)
{
	int		h;
	int		v;
	t_ray	horizontal;
	t_ray	vertical;

	ft_bzero(&horizontal, sizeof(t_ray));
	ft_bzero(&vertical, sizeof(t_ray));
	h = ray_cast_horizontal(mlx_info, &horizontal, angle);
	v = ray_cast_vertical(mlx_info, &vertical, angle);
	if (h < 0 || (vertical.length < horizontal.length && v >= 0))
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
