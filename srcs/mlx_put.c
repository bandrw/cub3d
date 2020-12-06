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

void	put_square(t_mlx *mlx_info, t_point *p, int size)
{
	int i;
	int j;

	i = p->x - size / 2;
	while (i < p->x + size / 2)
	{
		j = p->y - size / 2;
		while (j < p->y + size / 2)
		{
			mlx_pixel_put(mlx_info->init, mlx_info->window, i, j, 0xFF0000);
			j++;
		}
		i++;
	}
}
