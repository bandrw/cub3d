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

void	move_forward(t_mlx *mlx_info, float step)
{
	t_point		index;
	t_pointf	tmp;

	tmp.x = mlx_info->player.position.x +
				step * cosf(to_rad(mlx_info->player.angle));
	tmp.y = mlx_info->player.position.y -
				step * sinf(to_rad(mlx_info->player.angle));
	if (sinf(to_rad(mlx_info->player.angle)) > 0)
		index.y = (int)((tmp.y - 15.f) / 50.f);
	else
		index.y = (int)((tmp.y + 15.f) / 50.f);
	index.x = (int)(mlx_info->player.position.x / 50.f);
	if (mlx_info->map[index.y][index.x] == '0')
		mlx_info->player.position.y = tmp.y;
	index.y = (int)(mlx_info->player.position.y / 50.f);
	if (cosf(to_rad(mlx_info->player.angle)) > 0)
		index.x = (int)((tmp.x + 15.f) / 50.f);
	else
		index.x = (int)((tmp.x - 15.f) / 50.f);
	if (mlx_info->map[index.y][index.x] == '0')
		mlx_info->player.position.x = tmp.x;
}

void	move_backward(t_mlx *mlx_info, float step)
{
	t_point		index;
	t_pointf	tmp;

	tmp.x = mlx_info->player.position.x -
			step * cosf(to_rad(mlx_info->player.angle));
	tmp.y = mlx_info->player.position.y +
			step * sinf(to_rad(mlx_info->player.angle));
	if (sinf(to_rad(mlx_info->player.angle)) > 0)
		index.y = (int)((tmp.y + 15.f) / 50.f);
	else
		index.y = (int)((tmp.y - 15.f) / 50.f);
	index.x = (int)(mlx_info->player.position.x / 50.f);
	if (mlx_info->map[index.y][index.x] == '0')
		mlx_info->player.position.y = tmp.y;
	index.y = (int)(mlx_info->player.position.y / 50.f);
	if (cosf(to_rad(mlx_info->player.angle)) > 0)
		index.x = (int)((tmp.x - 15.f) / 50.f);
	else
		index.x = (int)((tmp.x + 15.f) / 50.f);
	if (mlx_info->map[index.y][index.x] == '0')
		mlx_info->player.position.x = tmp.x;
}

void	move_left(t_mlx *mlx_info, float step)
{
	t_point		index;
	t_pointf	tmp;

	tmp.x = mlx_info->player.position.x +
			step * cosf(to_rad(mlx_info->player.angle + 90.f));
	tmp.y = mlx_info->player.position.y -
			step * sinf(to_rad(mlx_info->player.angle + 90.f));
	if (cosf(to_rad(mlx_info->player.angle)) > 0)
		index.y = (int)((tmp.y - 15.f) / 50.f);
	else
		index.y = (int)((tmp.y + 15.f) / 50.f);
	index.x = (int)(mlx_info->player.position.x / 50.f);
	if (mlx_info->map[index.y][index.x] == '0')
		mlx_info->player.position.y = tmp.y;
	index.y = (int)(mlx_info->player.position.y / 50.f);
	if (sinf(to_rad(mlx_info->player.angle)) > 0)
		index.x = (int)((tmp.x - 15.f) / 50.f);
	else
		index.x = (int)((tmp.x + 15.f) / 50.f);
	if (mlx_info->map[index.y][index.x] == '0')
		mlx_info->player.position.x = tmp.x;
}

void	move_right(t_mlx *mlx_info, float step)
{
	t_point		index;
	t_pointf	tmp;

	tmp.x = mlx_info->player.position.x +
			step * cosf(to_rad(mlx_info->player.angle - 90.f));
	tmp.y = mlx_info->player.position.y -
			step * sinf(to_rad(mlx_info->player.angle - 90.f));
	if (cosf(to_rad(mlx_info->player.angle)) > 0)
		index.y = (int)((tmp.y + 15.f) / 50.f);
	else
		index.y = (int)((tmp.y - 15.f) / 50.f);
	index.x = (int)(mlx_info->player.position.x / 50.f);
	if (mlx_info->map[index.y][index.x] == '0')
		mlx_info->player.position.y = tmp.y;
	index.y = (int)(mlx_info->player.position.y / 50.f);
	if (sinf(to_rad(mlx_info->player.angle)) > 0)
		index.x = (int)((tmp.x + 15.f) / 50.f);
	else
		index.x = (int)((tmp.x - 15.f) / 50.f);
	if (mlx_info->map[index.y][index.x] == '0')
		mlx_info->player.position.x = tmp.x;
}
