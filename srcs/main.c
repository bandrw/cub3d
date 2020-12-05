/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 14:09:59 by kfriese           #+#    #+#             */
/*   Updated: 2020/12/05 14:09:59 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void *mlx_ptr;
void *win_ptr;
int current_x = 250;
int current_y = 250;

static void put_rectangle(int x, int y, int size)
{
	for (int i = x; i <= x + size; i++)
	{
		for (int j = y; j <= y + size; j++)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0xFFFFFF);
		}
	}
}

static int	key_handle(int key, void *param)
{
	(void)param;
	if (key == KEY_LEFT || key == KEY_A)
	{
		current_x -= 5;
		put_rectangle(current_x, current_y, 5);
	}
	else if (key == KEY_RIGHT || key == KEY_D)
	{
		current_x += 5;
		put_rectangle(current_x, current_y, 5);
	}
	else if (key == KEY_UP || key == KEY_W)
	{
		current_y -= 5;
		put_rectangle(current_x, current_y, 5);
	}
	else if (key == KEY_BOTTOM || key == KEY_S)
	{
		current_y += 5;
		put_rectangle(current_x, current_y, 5);
	}
	return (0);
}

int			main(void)
{
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Cub 3D");
	mlx_key_hook(win_ptr, &key_handle, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
