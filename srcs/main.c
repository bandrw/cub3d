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
	x = mlx_info->player.position.x;
	y = mlx_info->player.position.y;
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

static void		put_map(t_mlx *mlx_info, t_img *img_data)
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
				put_line(img_data, &line, 0x3b3b3b);
				line.angle = -90.f;
				put_line(img_data, &line, 0x3b3b3b);
				line.coordinate.x += 50.f;
				line.coordinate.y += 50.f;
				line.angle = 90.f;
				put_line(img_data, &line, 0x3b3b3b);
				line.angle = 180.f;
				put_line(img_data, &line, 0x3b3b3b);
			}
			j++;
		}
		i++;
	}
}

static void		main_render(t_mlx *mlx_info)
{
	float		i;
	t_img		img_data;
	float		cast;
	float		x_tmp;
	t_rectangle	rectangle;
	t_img		texture;
	int			width;
	int			height;

	img_data.img = mlx_new_image(mlx_info->init, 500, 500);
	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bits_per_pixel, &img_data.line_length, &img_data.endian);
	texture.img = mlx_xpm_file_to_image(mlx_info->init, "img/test.xpm", &texture.width, &texture.height);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
	i = mlx_info->player.angle - 30.f;
	x_tmp = 500.f;
	while (i < mlx_info->player.angle + 30.f)
	{
		cast = ray_cast(mlx_info, i);
		i += 0.5f;
		x_tmp -= 500.f / 120.f;
		rectangle.width = 1;
		rectangle.heigth = (int)(500.f * 50.f / (cast * cosf((mlx_info->player.angle - i) * 3.14f / 180.f)));
		if (rectangle.heigth > 499)
			rectangle.heigth = 499;
		rectangle.start.x = x_tmp;
		rectangle.start.y = (500.f - (float)rectangle.heigth) / 2.f;
		put_line_from_image(&texture, &img_data, (int)x_tmp, (int)((500.f - (float)rectangle.heigth) / 2.f), rectangle.heigth);
	}
	mlx_put_image_to_window(mlx_info->init, mlx_info->window, img_data.img, 0, 0);
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

static void		new_mlx(t_mlx *mlx_info, int width, int height, char *title)
{
	mlx_info->player.position.x = (float)width / 2.f;
	mlx_info->player.position.y = (float)height / 2.f;
	mlx_info->player.angle = 90.f;
	mlx_info->map = new_map();
	mlx_info->init = mlx_init();
	mlx_info->height = height;
	mlx_info->width = width;
	mlx_info->window = mlx_new_window(mlx_info->init, width, height, title);
}

int				main(void)
{
	t_mlx mlx_info;

	new_mlx(&mlx_info, 500, 500, "Kfriese's Cub 3D");
	mlx_do_key_autorepeaton(mlx_info.init);
	main_render(&mlx_info);
	mlx_hook(mlx_info.window, 2, 1L << 2, &key_press, &mlx_info);
	mlx_hook(mlx_info.window, 17, 0, &close_app, &mlx_info);
	mlx_loop(mlx_info.init);
	return (0);
}
