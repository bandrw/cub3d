/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:11:11 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/05 20:11:12 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	append_neighbors(t_list **queue, char **map, t_point *point)
{
	if (map[point->y - 1][point->x] > 0 && map[point->y - 1][point->x] != '1')
		ft_lstadd_back(queue, new_point(point->x, point->y - 1));
	if (map[point->y + 1][point->x] > 0 && map[point->y + 1][point->x] != '1')
		ft_lstadd_back(queue, new_point(point->x, point->y + 1));
	if (map[point->y][point->x - 1] > 0 && map[point->y][point->x - 1] != '1')
		ft_lstadd_back(queue, new_point(point->x - 1, point->y));
	if (map[point->y][point->x + 1] > 0 && map[point->y][point->x + 1] != '1')
		ft_lstadd_back(queue, new_point(point->x + 1, point->y));
}

static int	check_map(t_mlx *mlx_info, char **map)
{
	t_list	*queue;
	t_list	*tmp;
	t_point	*point;

	queue = 0;
	ft_lstadd_back(&queue, new_point((int)(mlx_info->player.position.x / 50.f),
							(int)(mlx_info->player.position.y / 50.f)));
	while (queue)
	{
		point = queue->content;
		if (map[point->y][point->x] > 0)
		{
			map[point->y][point->x] = map[point->y][point->x] * -1;
			if (!point_exists(mlx_info, map, point->x, point->y - 1) ||
				!point_exists(mlx_info, map, point->x, point->y + 1) ||
				!point_exists(mlx_info, map, point->x + 1, point->y) ||
				!point_exists(mlx_info, map, point->x - 1, point->y))
				return (1);
			append_neighbors(&queue, map, point);
		}
		tmp = queue;
		queue = queue->next;
		ft_lstdelone(tmp, free);
	}
	return (normalize_map(mlx_info, map));
}

static void	set_player_angle(t_mlx *mlx_info, char ch)
{
	if (ch == 'N')
		mlx_info->player.angle = 90.f;
	else if (ch == 'S')
		mlx_info->player.angle = -90.f;
	else if (ch == 'W')
		mlx_info->player.angle = 180.f;
	else
		mlx_info->player.angle = 0.f;
}

static int	parse_map_line(t_mlx *mlx_info, char **map, int i)
{
	int j;

	j = 0;
	while (map[i][j] != '\0')
	{
		if (map[i][j] == 'N' || map[i][j] == 'S' ||
			map[i][j] == 'W' || map[i][j] == 'E')
		{
			if (mlx_info->player.position.x != 0.f ||
					mlx_info->player.position.y != 0.f)
				return (1);
			mlx_info->player.position.x = (float)j * 50.f + 25.f;
			mlx_info->player.position.y = (float)i * 50.f + 25.f;
			set_player_angle(mlx_info, map[i][j]);
			map[i][j] = '0';
		}
		else if (map[i][j] == '2')
			mlx_info->sprites_count++;
		else if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0')
			throw_error("Invalid map");
		j++;
	}
	return (0);
}

int			parse_map(t_mlx *mlx_info, char **map)
{
	int len;
	int i;

	len = 0;
	while (map[len] != 0)
		len++;
	mlx_info->map_height = len;
	i = 0;
	while (map[i] != 0)
	{
		len = (int)ft_strlen(map[i]);
		if (len == 0 || !(ft_strchr(map[i], '0') ||
				ft_strchr(map[i], '1') || ft_strchr(map[i], '2')))
			throw_error("Invalid map");
		if (len > mlx_info->map_width)
			mlx_info->map_width = len;
		if (parse_map_line(mlx_info, map, i) != 0)
			return (1);
		i++;
	}
	if (check_map(mlx_info, map) != 0)
		return (2);
	read_sprites(mlx_info, map);
	return (0);
}
