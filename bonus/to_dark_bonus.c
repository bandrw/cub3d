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

unsigned int	to_dark(unsigned int color, int height)
{
	t_pixel pixel;

	pixel.red = color >> 16;
	pixel.green = color >> 8;
	pixel.blue = color >> 0;
	if (65.f / height > 1)
	{
		pixel.red /= 65.f / height;
		pixel.green /= 65.f / height;
		pixel.blue /= 65.f / height;
	}
	return ((pixel.red << 16) | (pixel.green << 8) | (pixel.blue << 0));
}
