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

#include <mlx.h>
#include <stdio.h>

#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_BOTTOM 125
#define KEY_UP 126

void *mlx_ptr;
void *win_ptr;
int current_x = 250;
int current_y = 250;

int 	key_handle(int key, void *param)
{
	(void)param;
	if (key == KEY_LEFT)
	{
		current_x--;
		mlx_pixel_put(mlx_ptr, win_ptr, current_x, current_y, 0xFFFFFF);
	}
	else if (key == KEY_RIGHT)
	{
		current_x++;
		mlx_pixel_put(mlx_ptr, win_ptr, current_x, current_y, 0xFFFFFF);
	}
	else if (key == KEY_UP)
	{
		current_y--;
		mlx_pixel_put(mlx_ptr, win_ptr, current_x, current_y, 0xFFFFFF);
	}
	else if (key == KEY_BOTTOM)
	{
		current_y++;
		mlx_pixel_put(mlx_ptr, win_ptr, current_x, current_y, 0xFFFFFF);
	}
	return (0);
}

int 	main(void)
{
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Cub 3D");
	mlx_key_hook(win_ptr, &key_handle, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
