/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 03:28:55 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/05 03:28:57 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_mlx *mlx_info)
{
	if (key == KEY_ESC)
		close_app(mlx_info);
	if (key == KEY_W)
		mlx_info->active_keys.w = 1;
	if (key == KEY_A)
		mlx_info->active_keys.a = 1;
	if (key == KEY_S)
		mlx_info->active_keys.s = 1;
	if (key == KEY_D)
		mlx_info->active_keys.d = 1;
	if (key == KEY_LEFT)
		mlx_info->active_keys.left_arrow = 1;
	if (key == KEY_RIGHT)
		mlx_info->active_keys.right_arrow = 1;
	return (0);
}

int		key_release(int key, t_mlx *mlx_info)
{
	if (key == KEY_W)
		mlx_info->active_keys.w = 0;
	if (key == KEY_A)
		mlx_info->active_keys.a = 0;
	if (key == KEY_S)
		mlx_info->active_keys.s = 0;
	if (key == KEY_D)
		mlx_info->active_keys.d = 0;
	if (key == KEY_LEFT)
		mlx_info->active_keys.left_arrow = 0;
	if (key == KEY_RIGHT)
		mlx_info->active_keys.right_arrow = 0;
	return (0);
}

int		key_handle(t_mlx *mlx_info)
{
	int		count;
	float	step;

	step = 3.5f;
	count = mlx_info->active_keys.w + mlx_info->active_keys.s +
			mlx_info->active_keys.a + mlx_info->active_keys.d;
	if (count == 2)
		step /= 1.7f;
	if (mlx_info->active_keys.w)
		move_forward(mlx_info, step);
	if (mlx_info->active_keys.a)
		move_left(mlx_info, step);
	if (mlx_info->active_keys.s)
		move_backward(mlx_info, step);
	if (mlx_info->active_keys.d)
		move_right(mlx_info, step);
	if (mlx_info->active_keys.left_arrow)
		change_direction(mlx_info, KEY_LEFT, 1.25f);
	if (mlx_info->active_keys.right_arrow)
		change_direction(mlx_info, KEY_RIGHT, 1.25f);
	main_render(mlx_info);
	return (0);
}

int		mouse_movement(int x, int y, t_mlx *mlx_info)
{
	float angle;

	(void)y;
	angle = ((float)x - (float)mlx_info->width / 2.f) / 60.f;
	change_direction(mlx_info, KEY_RIGHT, angle);
	mlx_mouse_move(mlx_info->window, mlx_info->width / 2, mlx_info->height / 2);
	return (0);
}
