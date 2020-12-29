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
	{
		if (mlx_info->player.angle == 0.f)
			mlx_info->player.angle = 359.f;
		else
			mlx_info->player.angle -= (float)step;
	}
	else if (key == KEY_LEFT)
	{
		if (mlx_info->player.angle == 359.f)
			mlx_info->player.angle = 0.f;
		else
			mlx_info->player.angle += (float)step;
	}
}

void	move(t_mlx *mlx_info, int key, float step)
{
	if (key == KEY_A)
		mlx_info->player.position.x -= step;
	else if (key == KEY_D)
		mlx_info->player.position.x += step;
	else if (key == KEY_W)
		mlx_info->player.position.y -= step;
	else if (key == KEY_S)
		mlx_info->player.position.y += step;
}
