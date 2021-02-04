/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:16:49 by kfriese           #+#    #+#             */
/*   Updated: 2020/12/06 15:16:51 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_direction(t_mlx *mlx_info, int key, float step)
{
	if (key == KEY_RIGHT)
		mlx_info->player.angle -= step;
	else if (key == KEY_LEFT)
		mlx_info->player.angle += step;
	while (mlx_info->player.angle > 180.f)
		mlx_info->player.angle -= 360.f;
	while (mlx_info->player.angle < -180.f)
		mlx_info->player.angle += 360.f;
}

void	move(t_mlx *mlx_info, int key, float step)
{
	t_point tmp;

	if (key == KEY_A)
	{
		tmp.x = mlx_info->player.position.x + step * cosf(to_rad(mlx_info->player.angle + 90.f));
		tmp.y = mlx_info->player.position.y - step * sinf(to_rad(mlx_info->player.angle + 90.f));
		if (mlx_info->map[(int)((tmp.y + (cosf(to_rad(mlx_info->player.angle)) > 0 ? -15.f : 15.f)) / 50.f)][(int)(mlx_info->player.position.x / 50.f)] == '0')
			mlx_info->player.position.y = tmp.y;
		if (mlx_info->map[(int)(mlx_info->player.position.y / 50.f)][(int)((tmp.x + (sinf(to_rad(mlx_info->player.angle)) > 0 ? -15.f : 15.f)) / 50.f)] == '0')
			mlx_info->player.position.x = tmp.x;
	}
	else if (key == KEY_D)
	{
		tmp.x = mlx_info->player.position.x + step * cosf(to_rad(mlx_info->player.angle - 90.f));
		tmp.y = mlx_info->player.position.y - step * sinf(to_rad(mlx_info->player.angle - 90.f));
		if (mlx_info->map[(int)((tmp.y + (cosf(to_rad(mlx_info->player.angle)) > 0 ? 15.f : -15.f)) / 50.f)][(int)(mlx_info->player.position.x / 50.f)] == '0')
			mlx_info->player.position.y = tmp.y;
		if (mlx_info->map[(int)(mlx_info->player.position.y / 50.f)][(int)((tmp.x + (sinf(to_rad(mlx_info->player.angle)) > 0 ? 15.f : -15.f)) / 50.f)] == '0')
			mlx_info->player.position.x = tmp.x;
	}
	else if (key == KEY_W)
	{
		tmp.x = mlx_info->player.position.x + step * cosf(to_rad(mlx_info->player.angle));
		tmp.y = mlx_info->player.position.y - step * sinf(to_rad(mlx_info->player.angle));
		if (mlx_info->map[(int)((tmp.y + (sinf(to_rad(mlx_info->player.angle)) > 0 ? -15.f : 15.f)) / 50.f)][(int)(mlx_info->player.position.x / 50.f)] == '0')
			mlx_info->player.position.y = tmp.y;
		if (mlx_info->map[(int)(mlx_info->player.position.y / 50.f)][(int)((tmp.x + (cosf(to_rad(mlx_info->player.angle)) > 0 ? 15.f : -15.f)) / 50.f)] == '0')
			mlx_info->player.position.x = tmp.x;
	}
	else if (key == KEY_S)
	{
		tmp.x = mlx_info->player.position.x - step * cosf(to_rad(mlx_info->player.angle));
		tmp.y = mlx_info->player.position.y + step * sinf(to_rad(mlx_info->player.angle));
		if (mlx_info->map[(int)((tmp.y + (sinf(to_rad(mlx_info->player.angle)) > 0 ? 15.f : -15.f)) / 50.f)][(int)(mlx_info->player.position.x / 50.f)] == '0')
			mlx_info->player.position.y = tmp.y;
		if (mlx_info->map[(int)(mlx_info->player.position.y / 50.f)][(int)((tmp.x + (cosf(to_rad(mlx_info->player.angle)) > 0 ? -15.f : 15.f)) / 50.f)] == '0')
			mlx_info->player.position.x = tmp.x;
	}
}
