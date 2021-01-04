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

void	change_direction(t_mlx *mlx_info, int key)
{
	int step;

	step = 5;
	if (key == KEY_RIGHT)
		mlx_info->player.angle -= (float)step;
	else if (key == KEY_LEFT)
		mlx_info->player.angle += (float)step;
}

void	move(t_mlx *mlx_info, int key, float step)
{
	t_point old;

	old = mlx_info->player.position;
	if (key == KEY_A)
	{
		mlx_info->player.position.y -= step * sinf(ft_to_radians(mlx_info->player.angle + 90.f));
		mlx_info->player.position.x += step * cosf(ft_to_radians(mlx_info->player.angle + 90.f));
	}
	else if (key == KEY_D)
	{
		mlx_info->player.position.y -= step * sinf(ft_to_radians(mlx_info->player.angle - 90.f));
		mlx_info->player.position.x += step * cosf(ft_to_radians(mlx_info->player.angle - 90.f));
	}
	else if (key == KEY_W)
	{
		mlx_info->player.position.y -= step * sinf(ft_to_radians(mlx_info->player.angle));
		mlx_info->player.position.x += step * cosf(ft_to_radians(mlx_info->player.angle));
	}
	else if (key == KEY_S)
	{
		mlx_info->player.position.y += step * sinf(ft_to_radians(mlx_info->player.angle));
		mlx_info->player.position.x -= step * cosf(ft_to_radians(mlx_info->player.angle));
	}
	if (mlx_info->map[(int)(mlx_info->player.position.y / 50)][(int)(mlx_info->player.position.x / 50)] == '1')
		mlx_info->player.position = old;
}
