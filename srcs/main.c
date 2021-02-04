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

static int		close_app(t_mlx *mlx_info)
{
	(void)mlx_info;
	//destroy(mlx_info);
	exit(0);
}

/*
static void		put_map(t_mlx *mlx_info, t_img *img_data)
{
	int i;
	int j;
	int len;
	t_rectangle rectangle;

	i = 0;
	while (i < mlx_info->map_height)
	{
		j = 0;
		len = (int)ft_strlen(mlx_info->map[i]);
		while (j < len)
		{
			if (mlx_info->map[i][j] == '1')
			{
				rectangle.start.x = (float)j * 50.f - mlx_info->player.position.x + mlx_info->width / 2.f;
				rectangle.start.y = (float)i * 50.f - mlx_info->player.position.y + mlx_info->height / 2.f;
				rectangle.width = 50;
				rectangle.height = 1;
				put_rectangle(img_data, &rectangle, 0x3B3B3B);
				rectangle.width = 1;
				rectangle.height = 50;
				put_rectangle(img_data, &rectangle, 0x3B3B3B);
				rectangle.start.x += 50;
				put_rectangle(img_data, &rectangle, 0x3B3B3B);
				rectangle.start.y += 50.f;
				rectangle.start.x -= 50.f;
				rectangle.width = 50;
				rectangle.height = 1;
				put_rectangle(img_data, &rectangle, 0x3B3B3B);
			}
			j += 1;
		}
		i += 1;
	}
}

static void		render_2d(t_mlx *mlx_info, t_img *img_data)
{
	t_ray cast;
	t_line line;
	t_rectangle player;
	t_rectangle sprite;
	float angle;
	t_sprite *item;
	t_list *tmp;

	player.height = 8;
	player.width = 8;
	player.start.x = (float)mlx_info->width / 2.f - player.width / 2.f;
	player.start.y = (float)mlx_info->height / 2.f - player.height / 2.f;
	angle = mlx_info->player.angle - 33.f;
	while (angle < mlx_info->player.angle + 33.f)
	{
		ray_cast(mlx_info, &cast, angle);
		line.angle = angle;
		line.length = cast.length;
		line.coordinate.x = player.start.x + player.width / 2.f;
		line.coordinate.y = player.start.y + player.width / 2.f;
		put_line(img_data, &line, 0xDDDDDD);
		tmp = cast.sprites;
		while (tmp)
		{
			item = tmp->content;
			sprite.width = 5;
			sprite.height = 5;
			sprite.start.x = (float)mlx_info->width / 2.f + item->length * cosf(ft_to_radians(angle));
			sprite.start.y = (float)mlx_info->height / 2.f - item->length * sinf(to_rad(angle));
			put_rectangle(img_data, &sprite, 0xFF0000);
			tmp = tmp->next;
		}
		ft_lstclear(&cast.sprites, 0);
		angle += 66.f / (float)mlx_info->width;
	}
	put_rectangle(img_data, &player, 0x00FF00);
	put_map(mlx_info, img_data);
}
*/

void			put_ceilling_and_floor(t_mlx *mlx_info)
{
	t_rectangle rectangle;

	rectangle.width = mlx_info->width;
	rectangle.height = mlx_info->height / 2;
	rectangle.start.x = 0;
	rectangle.start.y = 0;
	put_rectangle(&mlx_info->stage, &rectangle, mlx_info->ceiling_color);
	rectangle.start.y = (float)mlx_info->height / 2.f;
	put_rectangle(&mlx_info->stage, &rectangle, mlx_info->floor_color);
}

void			clear_stage(t_img *stage)
{
	int i;
	int j;

	i = 0;
	while (i < stage->width)
	{
		j = 0;
		while (j < stage->height)
		{
			img_pixel_put(stage, i, j, 0);
			j++;
		}
		i++;
	}
}

void			main_render(t_mlx *mlx_info)
{
	float	lengths[mlx_info->width];
	int x_tmp;
	float angle;
	t_ray cast;
	t_img texture;
	int height;
	int x_src;
	int i;

	if (mlx_info->window)
	{
		mlx_mouse_hide();
		mlx_clear_window(mlx_info->init, mlx_info->window);
	}
	put_ceilling_and_floor(mlx_info);
	angle = mlx_info->player.angle + 33.f;
	x_tmp = 0;
	while (x_tmp < mlx_info->width)
	{
		ft_bzero(&cast, sizeof(cast));
		ray_cast(mlx_info, &cast, angle);
		if (cast.direction == North)
			texture = mlx_info->north_texture;
		else if (cast.direction == West)
			texture = mlx_info->west_texture;
		else if (cast.direction == South)
			texture = mlx_info->south_texture;
		else
			texture = mlx_info->east_texture;
		height = (int)((float)mlx_info->width * 40.f / (cast.length * cosf(
				to_rad(mlx_info->player.angle - angle))));
		if (cast.direction == West || cast.direction == East)
			x_src = (int)((float)texture.width * fmodf(cast.end.y, 50.f) / 50.f);
		else
			x_src = (int)((float)texture.width * fmodf(cast.end.x, 50.f) / 50.f);
		i = -1;
		if (height > mlx_info->height)
		{
			while (++i < mlx_info->height)
				img_pixel_put(&mlx_info->stage, x_tmp, i, img_get_pixel(&texture, x_src, (int)((float)texture.height / ((float)height / ((float)i + (float)(height - mlx_info->height) / 2.f)))));
		}
		else
		{
			while (++i < height)
				img_pixel_put(&mlx_info->stage, x_tmp, (int)((float)(mlx_info->height - height) / 2.f) + i, img_get_pixel(&texture, x_src, (int)((float)i / (float)height * (float)texture.height)));
		}
		lengths[x_tmp] = cast.length;
		angle -= 66.f / (float)mlx_info->width;
		x_tmp++;
	}
	put_sprites(mlx_info, lengths);
	if (mlx_info->window)
		mlx_put_image_to_window(mlx_info->init, mlx_info->window, mlx_info->stage.img, 0, 0);
}

static int		key_press(int key, t_mlx *mlx_info)
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

static int		key_release(int key, t_mlx *mlx_info)
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

static int		key_handle(t_mlx *mlx_info)
{
	int		count;
	float	step;

	step = 3.5f;
	count = mlx_info->active_keys.w + mlx_info->active_keys.s +
			mlx_info->active_keys.a + mlx_info->active_keys.d;
	if (count == 2)
		step /= 1.7f;
	if (mlx_info->active_keys.w)
		move(mlx_info, KEY_W, step);
	if (mlx_info->active_keys.a)
		move(mlx_info, KEY_A, step);
	if (mlx_info->active_keys.s)
		move(mlx_info, KEY_S, step);
	if (mlx_info->active_keys.d)
		move(mlx_info, KEY_D, step);
	if (mlx_info->active_keys.left_arrow)
		change_direction(mlx_info, KEY_LEFT, 1.25f);
	if (mlx_info->active_keys.right_arrow)
		change_direction(mlx_info, KEY_RIGHT, 1.25f);
	main_render(mlx_info);
	return (0);
}

static int		mouse_movement(int x, int y, t_mlx *mlx_info)
{
	float angle;

	(void)y;
	angle = ((float)x - (float)mlx_info->width / 2.f) / 60.f;
	change_direction(mlx_info, KEY_RIGHT, angle);
	mlx_mouse_move(mlx_info->window, mlx_info->width / 2, mlx_info->height / 2);
	return (0);
}

void			new_mlx(t_mlx *mlx_info, char *file, char *title, int out)
{
	ft_bzero(mlx_info, sizeof(*mlx_info));
	mlx_info->init = mlx_init();
	mlx_info->window = (void *)out;
	parse_config(mlx_info, file);
	if (out)
		mlx_info->window = mlx_new_window(mlx_info->init, mlx_info->width, mlx_info->height, title);
	mlx_info->stage.width = mlx_info->width;
	mlx_info->stage.height = mlx_info->height;
	mlx_info->stage.img = mlx_new_image(mlx_info->init, mlx_info->width, mlx_info->height);
	mlx_info->stage.addr = mlx_get_data_addr(mlx_info->stage.img, &mlx_info->stage.bits_per_pixel, &mlx_info->stage.line_length, &mlx_info->stage.endian);
}

void			check_arg(int argc, char **argv)
{
	char *p;

	if (argc == 2 || argc == 3)
	{
		p = ft_strrchr(argv[1], '.');
		if (!p || ft_strncmp(p, ".cub", 5))
			simple_error("Invalid arguments");
		if (argc == 3 && ft_strncmp(argv[2], "--save", 7) != 0)
			simple_error("Invalid arguments");
	}
	else
		usage_error(argv[0]);
}

int				main(int argc, char **argv)
{
	t_mlx mlx_info;

	check_arg(argc, argv);
	if (argc == 2)
	{
		new_mlx(&mlx_info, argv[1], "Kfriese's Cub 3D", 1);
		mlx_mouse_move(mlx_info.window, mlx_info.width / 2, mlx_info.height / 2);
		mlx_hook(mlx_info.window, 2, 1L << 1, key_press, &mlx_info);
		mlx_hook(mlx_info.window, 3, 0, key_release, &mlx_info);
		mlx_hook(mlx_info.window, 6, 0, mouse_movement, &mlx_info);
		mlx_hook(mlx_info.window, 17, 1L << 17, close_app, &mlx_info);
		mlx_loop_hook(mlx_info.init, key_handle, &mlx_info);
		mlx_loop(mlx_info.init);
	}
	else if (argc == 3)
	{
		new_mlx(&mlx_info, argv[1], "Kfriese's Cub 3D", 0);
		save_image(&mlx_info, "out.bmp");
	}
	return (0);
}
