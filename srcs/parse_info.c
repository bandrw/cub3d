/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:52:27 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/05 20:52:29 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_render_size(t_mlx *mlx_info, char *str)
{
	int		i;
	t_point	max;

	mlx_get_screen_size(mlx_info->init, &max.x, &max.y);
	i = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		throw_error("Map error: Resolution");
	mlx_info->width = ft_atoi(str + i);
	i += ft_nbrlen(mlx_info->width);
	if (mlx_info->window && mlx_info->width > max.x)
		mlx_info->width = max.x;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		throw_error("Map error: Resolution");
	mlx_info->height = ft_atoi(str + i);
	if (mlx_info->window && mlx_info->height > max.y)
		mlx_info->height = max.y;
}

void	parse_texture(t_mlx *mlx_info, char *str)
{
	int i;

	if (str[1] == '\0')
		throw_error("Map error: Sprite");
	i = 2;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		throw_error("Map error: Bad textures");
	if (ft_strncmp(str, "NO", 2) == 0)
		new_texture(mlx_info, &mlx_info->north_texture, str + i);
	else if (ft_strncmp(str, "SO", 2) == 0)
		new_texture(mlx_info, &mlx_info->south_texture, str + i);
	else if (ft_strncmp(str, "WE", 2) == 0)
		new_texture(mlx_info, &mlx_info->west_texture, str + i);
	else if (ft_strncmp(str, "EA", 2) == 0)
		new_texture(mlx_info, &mlx_info->east_texture, str + i);
	else if (*str == 'S')
		new_texture(mlx_info, &mlx_info->sprite_texture, str + i);
}

void	parse_color(t_mlx *mlx_info, const char *str)
{
	int		i;
	int		color;
	char	**arr;

	i = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		throw_error("Can't parse color");
	arr = ft_split(str + i, ',');
	i = 0;
	while (arr[i] != 0)
		i++;
	if (i != 3)
		throw_perror("Can't parse color");
	color = (ft_atoi(arr[0]) << 16) | (ft_atoi(arr[1]) << 8) |
			(ft_atoi(arr[2]) << 0);
	if (*str == 'F')
		mlx_info->floor_color = color;
	else
		mlx_info->ceiling_color = color;
	while (i-- < 3)
		free(arr[i]);
	free(arr);
}
