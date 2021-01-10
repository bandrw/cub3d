/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 06:38:39 by kfriese           #+#    #+#             */
/*   Updated: 2021/01/10 06:38:39 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../includes/cub3d.h"

t_sprite	*new_sprite(float length, float x, float y)
{
	t_sprite *sprite;

	sprite = (t_sprite*)malloc(sizeof(t_sprite));
	if (!sprite)
		exit(3);
	sprite->length = length;
	sprite->end.x = x;
	sprite->end.y = y;
	return (sprite);
}
