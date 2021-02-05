/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 03:28:39 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/05 03:28:41 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	to_rad(float degrees)
{
	return (degrees * (float)M_PI / 180.f);
}

float	to_deg(float radians)
{
	return (radians * 180.f / (float)M_PI);
}
