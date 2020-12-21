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
# include "../minilibx/mlx.h"

static int		close_app(t_mlx *mlx_info)
{
	(void)mlx_info;
	//destroy(mlx_info);
	exit(0);
}

static float	ray_cast(t_mlx *mlx_info, float angle)
{
	int i;
	int j;
	float x;
	float y;
	float distance;
	float step;
	float x_k;
	float y_k;

	step = 1.f;
	distance = 0.f;
	x = mlx_info->player->position->x;
	y = mlx_info->player->position->y;
	i = (int)(10.f * x / (float)mlx_info->width); // 10.f - map size
	j = (int)(10.f * y / (float)mlx_info->height);
	x_k = cosf(angle * 3.14f / 180.f);
	y_k = sinf(angle * 3.14f / 180.f);
	while (i >= 0 && i < 10 && j >= 0 && j < 10 && mlx_info->map[j][i] != '1') // 10 - map size
	{
		x += step * x_k;
		y -= step * y_k;
		i = (int)(10.f * x / (float)mlx_info->width);
		j = (int)(10.f * y / (float)mlx_info->height);
		distance += step;
	}
	return (distance);
}

static void		put_map(t_mlx *mlx_info)
{
	float i;
	float j;
	t_line line;

	line.length = 50.f;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (mlx_info->map[(int)i][(int)j] == '1')
			{
				line.angle = 0.f;
				line.coordinate.x = j * 50.f;
				line.coordinate.y = i * 50.f;
				put_line(mlx_info, &line, 0x3b3b3b);
				line.angle = -90.f;
				put_line(mlx_info, &line, 0x3b3b3b);
				line.coordinate.x += 50.f;
				line.coordinate.y += 50.f;
				line.angle = 90.f;
				put_line(mlx_info, &line, 0x3b3b3b);
				line.angle = 180.f;
				put_line(mlx_info, &line, 0x3b3b3b);
			}
			j++;
		}
		i++;
	}
}

static void		main_render(t_mlx *mlx_info)
{
	t_line line;
	float i;

	// 60 degrees view
	i = mlx_info->player->angle - 30.f;
	while (i < mlx_info->player->angle + 30.f)
	{
		line.coordinate.x = mlx_info->player->position->x;
		line.coordinate.y = mlx_info->player->position->y;
		line.length = ray_cast(mlx_info, i);
		line.angle = i;
		put_line(mlx_info, &line, 0xEEEEEE);
		i += 1.f;
	}

	// one line
//	line.coordinate.x = mlx_info->player->position->x;
//	line.coordinate.y = mlx_info->player->position->y;
//	line.length = ray_cast(mlx_info, mlx_info->player->angle);
//	line.angle = mlx_info->player->angle;
//	put_line(mlx_info, &line, 0xEEEEEE);

	put_map(mlx_info);

	t_point tmp_point;
	tmp_point.x = mlx_info->player->position->x - 5;
	tmp_point.y = mlx_info->player->position->y - 5;
	put_square(mlx_info, tmp_point, 10, 0x00FF00);

	// length output
//	char tmp[100];
//	sprintf(tmp, "length = %f", line.length);
//	mlx_string_put(mlx_info->init, mlx_info->window, 10, 10, 0xFFFFFF, tmp);
}

static int		key_press(int key, t_mlx *mlx_info)
{
	float step;

	step = 10.f;
	if (key == KEY_ESC)
		close_app(mlx_info);
	if (is_moveable(key) || is_arrow(key))
		mlx_clear_window(mlx_info->init, mlx_info->window);
	if (is_moveable(key))
		move(mlx_info, key, step);
	if (is_arrow(key))
		change_direction(mlx_info, key);
	if (is_moveable(key) || is_arrow(key))
		main_render(mlx_info);
	return (0);
}

static t_player	*new_player(float width, float height)
{
	t_player *player;

	if ((player = (t_player*)malloc(sizeof(t_player))) == 0)
		return (0);
	if ((player->position = (t_point*)malloc(sizeof(t_point))) == 0)
	{
		free(player);
		return (0);
	}
	player->position->x = width / 2.f;
	player->position->y = height / 2.f;
	player->angle = 90.f;
	return (player);
}

static t_mlx	*new_mlx(int width, int height, char *title)
{
	t_mlx *mlx_info;

	if ((mlx_info = (t_mlx*)malloc(sizeof(t_mlx))) == 0)
		return (0);
	if ((mlx_info->player = new_player((float)width, (float)height)) == 0)
	{
		free(mlx_info);
		return (0);
	}
	if (!(mlx_info->map = new_map()))
	{
		free(mlx_info->player);
		free(mlx_info);
		return (0);
	}
	mlx_info->init = mlx_init();
	mlx_info->height = height;
	mlx_info->width = width;
	mlx_info->window = mlx_new_window(mlx_info->init, width, height, title);
	return (mlx_info);
}

int				main(void)
{
	t_mlx *mlx_info;

	if (!(mlx_info = new_mlx(500, 500, "Kfriese's Cub 3D")))
		return (1);
	main_render(mlx_info);
	mlx_hook(mlx_info->window, 2, 0, &key_press, mlx_info);
	mlx_hook(mlx_info->window, 17, 0, &close_app, mlx_info);
	mlx_loop(mlx_info->init);
	return (0);
}
