/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:42:48 by kfriese           #+#    #+#             */
/*   Updated: 2020/12/06 15:42:49 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**new_map(void)
{
	char	**map;

	if (!(map = (char**)malloc(sizeof(char*) * 10)))
		return (0);
	map[0] = ft_strdup("1111111111");
	map[1] = ft_strdup("1000000001");
	map[2] = ft_strdup("1000000001");
	map[3] = ft_strdup("1000000001");
	map[4] = ft_strdup("1000000001");
	map[5] = ft_strdup("1000000001");
	map[6] = ft_strdup("1000000001");
	map[7] = ft_strdup("1000000001");
	map[8] = ft_strdup("1000000001");
	map[9] = ft_strdup("1111111111");
	return (map);
}
