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
	if (key == KEY_RIGHT)
	{
		if (mlx_info->player->angle == 0)
			mlx_info->player->angle = 360;
		else
			mlx_info->player->angle--;
	}
	else if (key == KEY_LEFT)
	{
		if (mlx_info->player->angle == 360)
			mlx_info->player->angle = 0;
		else
			mlx_info->player->angle++;
	}
	ft_printf("Angle: %d\n", mlx_info->player->angle);
}

void	move(t_mlx *mlx_info, int key, int step)
{
	if (key == KEY_A)
		mlx_info->player->position->x -= step;
	else if (key == KEY_D)
		mlx_info->player->position->x += step;
	else if (key == KEY_W)
		mlx_info->player->position->y -= step;
	else if (key == KEY_S)
		mlx_info->player->position->y += step;
	ft_printf("x: %d, y: %d\n", mlx_info->player->position->x, mlx_info->player->position->y);
}
