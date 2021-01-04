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
	float	angle;
	t_ray	cast;
	float	x_tmp;
	t_img	img_data;
	t_img	texture;
	int		height;
	int		x_src;

	img_data.img = mlx_new_image(mlx_info->init, 500, 500);
	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bits_per_pixel, &img_data.line_length, &img_data.endian);
	texture.img = mlx_xpm_file_to_image(mlx_info->init, "img/test.xpm", &texture.width, &texture.height);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
	x_tmp = 0;
	angle = mlx_info->player.angle + 33.f;
	while (x_tmp < 500)
	{
		ray_cast(mlx_info, &cast, angle);
		height = (int)(500.f * 50.f / (cast.length * cosf(ft_to_radians(mlx_info->player.angle - angle))));
		if (height > 500)
			height = 500;
		if (cast.direction == West || cast.direction == East)
			x_src = (int)(64 * (float)(cast.end.y - (float)((int)cast.end.y / 50 * 50)) / 50.f);
		else
			x_src = (int)(64 * (float)(cast.end.x - (float)((int)cast.end.x / 50 * 50)) / 50.f);
		put_line_from_image(&texture, &img_data, (int)x_tmp, (int)((500.f - (float)height) / 2.f), height, x_src);
		angle -= 66.f / 500.f;
		x_tmp++;
	}
//	put_map(mlx_info, &img_data);
//	rectangle.width = 8;
//	rectangle.heigth = 8;
//	rectangle.start.x = mlx_info->player.position.x - 4;
//	rectangle.start.y = mlx_info->player.position.y - 4;
//	put_rectangle(&img_data, &rectangle, 0xFFFF00);
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
