/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_dark_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:17:55 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/06 14:17:56 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	to_dark(t_mlx *mlx_info, unsigned int color, int height)
{
	t_pixel pixel;

	pixel.red = color >> 16;
	pixel.green = color >> 8;
	pixel.blue = color >> 0;
	if (((float)mlx_info->height / (float)height) * 0.125f > 1.f)
	{
		pixel.red /= ((float)mlx_info->height / (float)height) * 0.125f;
		pixel.green /= ((float)mlx_info->height / (float)height) * 0.125f;
		pixel.blue /= ((float)mlx_info->height / (float)height) * 0.125f;
	}
	return ((pixel.red << 16) | (pixel.green << 8) | (pixel.blue << 0));
}
