/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 03:23:15 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/05 03:23:17 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*get_texture(t_mlx *mlx_info, t_direction direction)
{
	if (direction == North)
		return (&mlx_info->north_texture);
	else if (direction == West)
		return (&mlx_info->west_texture);
	else if (direction == South)
		return (&mlx_info->south_texture);
	else
		return (&mlx_info->east_texture);
}

static void		draw_line(t_mlx *mlx_info, t_ray *cast, int height, int x_tmp)
{
	int		i;
	int		x_src;
	t_img	*texture;

	texture = get_texture(mlx_info, cast->direction);
	if (cast->direction == West || cast->direction == East)
		x_src = (int)((float)texture->width * fmodf(cast->end.y, 50.f) / 50.f);
	else
		x_src = (int)((float)texture->width * fmodf(cast->end.x, 50.f) / 50.f);
	i = -1;
	if (height > mlx_info->height)
	{
		while (++i < mlx_info->height)
			img_pixel_put(&mlx_info->stage, x_tmp, i, img_get_pixel(texture,
				x_src, (int)((float)texture->height / ((float)height /
				((float)i + (float)(height - mlx_info->height) / 2.f)))));
	}
	else
	{
		while (++i < height)
			img_pixel_put(&mlx_info->stage, x_tmp,
				(int)((float)(mlx_info->height - height) / 2.f) + i,
				img_get_pixel(texture, x_src, (int)((float)i / (float)height *
				(float)texture->height)));
	}
}

static void		render_line(t_mlx *mlx_info, int x_tmp,
						float lengths[mlx_info->width], float angle)
{
	t_ray	cast;
	int		height;

	ft_bzero(&cast, sizeof(cast));
	ray_cast(mlx_info, &cast, angle);
	height = (int)((float)mlx_info->width * 40.f / (cast.length * cosf(
			to_rad(mlx_info->player.angle - angle))));
	draw_line(mlx_info, &cast, height, x_tmp);
	lengths[x_tmp] = cast.length;
}

void			main_render(t_mlx *mlx_info)
{
	int		x_tmp;
	float	angle;
	float	lengths[mlx_info->width];

	if (mlx_info->window)
		mlx_mouse_hide();
	put_ceilling_and_floor(mlx_info);
	angle = mlx_info->player.angle + 33.f;
	x_tmp = 0;
	while (x_tmp < mlx_info->width)
	{
		render_line(mlx_info, x_tmp, lengths, angle);
		angle -= 66.f / (float)mlx_info->width;
		x_tmp++;
	}
	put_sprites(mlx_info, lengths);
	if (mlx_info->window)
		mlx_put_image_to_window(mlx_info->init, mlx_info->window,
				mlx_info->stage.img, 0, 0);
}
