/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:45:42 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/05 20:45:45 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			normalize_map(t_mlx *mlx_info, char **map)
{
	int i;
	int j;

	i = 0;
	while (i < mlx_info->map_height)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] < 0)
				map[i][j] *= -1;
			j++;
		}
		i++;
	}
	return (0);
}

t_list		*new_point(int x, int y)
{
	t_list	*list;
	t_point	*point;

	if ((point = (t_point*)malloc(sizeof(t_point))) == 0)
		throw_error("Can't allocate point");
	point->x = x;
	point->y = y;
	if ((list = ft_lstnew(point)) == 0)
		throw_error("Can't allocate list");
	return (list);
}

int			point_exists(t_mlx *mlx_info, char **map, int x, int y)
{
	return (y >= 0 && y < mlx_info->map_height &&
			x < (int)ft_strlen(map[y]) && x >= 0 &&
			map[y][x] != ' ');
}

void		read_sprites(t_mlx *mlx_info, char **map)
{
	int i;
	int j;
	int k;

	if (!(mlx_info->sprites = (t_sprite*)ft_calloc(mlx_info->sprites_count,
													sizeof(t_sprite))))
		throw_error("Can't allocate sprites");
	k = 0;
	i = 0;
	while (i < mlx_info->map_height)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '2')
			{
				mlx_info->sprites[k].y_index = i;
				mlx_info->sprites[k].x_index = j;
				k++;
			}
			j++;
		}
		i++;
	}
}

void		new_texture(t_mlx *mlx_info, t_img *texture, char *file)
{
	texture->img = mlx_xpm_file_to_image(mlx_info->init, file, &texture->width,
											&texture->height);
	if (texture->img == 0)
		throw_perror(file);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
									&texture->line_length, &texture->endian);
}
