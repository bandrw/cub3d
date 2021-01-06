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
	int i;
	int j;
	t_rectangle rectangle;

	i = 0;
	while (i < mlx_info->map_height)
	{
		j = 0;
		while (j < mlx_info->map_width)
		{
			if (mlx_info->map[i][j] == '1')
			{
				rectangle.start.x = (float)mlx_info->width / 2.f - 50.f * (mlx_info->player.position.x / (float)mlx_info->width * (float)mlx_info->map_width - (float)j);
				rectangle.start.y = (float)mlx_info->height / 2.f - 50.f * (mlx_info->player.position.y / (float)mlx_info->height * (float)mlx_info->map_height - (float)i);
				rectangle.width = 50;
				rectangle.heigth = 1;
				put_rectangle(img_data, &rectangle, 0x3B3B3B);
				rectangle.width = 1;
				rectangle.heigth = 50;
				put_rectangle(img_data, &rectangle, 0x3B3B3B);
				rectangle.start.x += 50;
				put_rectangle(img_data, &rectangle, 0x3B3B3B);
				rectangle.start.y += 50.f;
				rectangle.start.x -= 50.f;
				rectangle.width = 50;
				rectangle.heigth = 1;
				put_rectangle(img_data, &rectangle, 0x3B3B3B);
			}
			j += 1;
		}
		i += 1;
	}
}

static void		render_2d(t_mlx *mlx_info, t_img *img_data)
{
	t_rectangle player;
	t_line line;
	t_ray cast;

	ray_cast(mlx_info, &cast, mlx_info->player.angle);
	player.start.x = (float)mlx_info->width / 2.f - 4.f;
	player.start.y = (float)mlx_info->height / 2.f - 4.f;
	player.heigth = 8;
	player.width = 8;
	put_rectangle(img_data, &player, 0x00FF00);
	line.angle = mlx_info->player.angle;
	line.length = cast.length;
	line.coordinate.x = player.start.x + 4.f;
	line.coordinate.y = player.start.y + 4.f;
	put_line(img_data, &line, 0x00FF00);
	put_map(mlx_info, img_data);
}

void			put_ceilling_and_floor(t_mlx *mlx_info, t_img *img_data)
{
	t_rectangle rectangle;

	rectangle.width = mlx_info->width;
	rectangle.heigth = mlx_info->height / 2;
	rectangle.start.x = 0;
	rectangle.start.y = 0;
	put_rectangle(img_data, &rectangle, mlx_info->ceilling_color);
	rectangle.start.y = (float)mlx_info->height / 2.f;
	put_rectangle(img_data, &rectangle, mlx_info->floor_color);
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

	img_data.width = mlx_info->width;
	img_data.height = mlx_info->height;
	img_data.img = mlx_new_image(mlx_info->init, mlx_info->width, mlx_info->height);
	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bits_per_pixel, &img_data.line_length, &img_data.endian);
//	put_ceilling_and_floor(mlx_info, &img_data);
	render_2d(mlx_info, &img_data);
//	texture.img = mlx_xpm_file_to_image(mlx_info->init, "img/test.xpm", &texture.width, &texture.height);
//	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
//	x_tmp = 0;
//	angle = mlx_info->player.angle + 33.f;
//	while (x_tmp < (float)mlx_info->width)
//	{
//		ray_cast(mlx_info, &cast, angle);
//		height = (int)((float)mlx_info->height * 40.f / (cast.length * cosf(ft_to_radians(mlx_info->player.angle - angle))));
//		if (height > mlx_info->height)
//			height = mlx_info->height;
//		if (cast.direction == West || cast.direction == East)
//			x_src = (int)((float)texture.width * (float)(cast.end.y - (float)((int)cast.end.y / 50 * 50)) / 50.f);
//		else
//			x_src = (int)((float)texture.width * (float)(cast.end.x - (float)((int)cast.end.x / 50 * 50)) / 50.f);
//		put_line_from_image(&texture, &img_data, (int)x_tmp, (int)((500.f - (float)height) / 2.f), height, x_src);
//		angle -= 66.f / (float)mlx_info->width;
//		x_tmp++;
//	}
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

static void		new_mlx(t_mlx *mlx_info, char *file, char *title)
{
	parse_config(mlx_info, file);
//	printf("Size: %d %d\n", mlx_info->width, mlx_info->height);
//	printf("NO: %s\n", mlx_info->north_tetxture);
//	printf("SO: %s\n", mlx_info->south_texture);
//	printf("WE: %s\n", mlx_info->west_texture);
//	printf("EA: %s\n", mlx_info->east_texture);
//	printf("Sprite: %s\n", mlx_info->sprite_texture);
//	printf("Floor: %.6X\n", mlx_info->floor_color);
//	printf("Ceiling: %.6X\n", mlx_info->ceilling_color);
//	int i = 0;
//	while (mlx_info->map[i] != 0)
//	{
//		printf("%s\n", mlx_info->map[i]);
//		i++;
//	}
	mlx_info->init = mlx_init();
	mlx_info->window = mlx_new_window(mlx_info->init, mlx_info->width, mlx_info->height, title);
}

int				main(int argc, char **argv)
{
	t_mlx mlx_info;

	if (argc != 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" map.cub\n", 2);
		return (1);
	}
	new_mlx(&mlx_info, argv[1], "Kfriese's Cub 3D");
	main_render(&mlx_info);
	mlx_hook(mlx_info.window, 2, 1L << 2, &key_press, &mlx_info);
	mlx_hook(mlx_info.window, 17, 0, &close_app, &mlx_info);
	mlx_loop(mlx_info.init);
	return (0);
}
