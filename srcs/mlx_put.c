/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:18:42 by kfriese           #+#    #+#             */
/*   Updated: 2020/12/06 15:18:43 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	ft_absf(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	img_pixel_put(t_img *img_data, int x, int y, int color)
{
	char *dst;

	dst = img_data->addr + (y * img_data->line_length + x * (img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_square(t_img *img_data, t_point p, float size, int color)
{
	float i;
	float j;

	i = p.x;
	while (i < p.x + size)
	{
		j = p.y;
		while (j < p.y + size)
		{
			img_pixel_put(img_data, (int)i, (int)j, color);
			j++;
		}
		i++;
	}
}

void	put_rectangle(t_img *img_data, t_rectangle *rectangle, int color)
{
	int start_x;
	int start_y;
	int i;
	int j;

	start_x = (int)rectangle->start.x;
	start_y = (int)rectangle->start.y;
	i = start_x;
	while (i < start_x + rectangle->width)
	{
		j = start_y;
		while (j < start_y + rectangle->heigth)
		{
			img_pixel_put(img_data->img, i, j, color);
			j++;
		}
		i++;
	}
}

void	put_line(t_img *img_data, t_line *line, int color)
{
	t_point p2;
	int tmp;
	int delta;
	float k;
	float x_projection;
	float y_projection;

	x_projection = ft_absf(line->length * cosf(line->angle * 3.14f / 180.f));
	y_projection = ft_absf(line->length * sinf(line->angle * 3.14f / 180.f));
	k = tanf(line->angle * 3.14f / 180.f);
	p2.x = line->coordinate.x + line->length * cosf(line->angle * 3.14f / 180.f);
	p2.y = line->coordinate.y - line->length * sinf(line->angle * 3.14f / 180.f);
	delta = 1;
	if (x_projection > y_projection)
	{
		tmp = (int)line->coordinate.x;
		if (p2.x < line->coordinate.x)
			delta = -1;
		while (ft_absf((float)tmp - line->coordinate.x) < x_projection)
		{
			img_pixel_put(img_data, tmp, (int)(line->coordinate.y - (ft_absf((float)tmp) - line->coordinate.x) * k), color);
			tmp += delta;
		}
	}
	else
	{
		tmp = (int)line->coordinate.y;
		if (p2.y < line->coordinate.y)
			delta = -1;
		while (ft_absf((float)tmp - line->coordinate.y) < y_projection)
		{
			img_pixel_put(img_data, (int)(line->coordinate.x - ((float)tmp - line->coordinate.y) / k), tmp, color);
			tmp += delta;
		}
	}
}
