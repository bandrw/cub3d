/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:37:05 by kfriese           #+#    #+#             */
/*   Updated: 2021/01/07 12:37:09 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../includes/cub3d.h"
#include "../libft/includes/libft.h"
//todo rm "../shit.h"

static char **read_config(int fd)
{
	char **arr;
	char *line;
	t_list *config;
	int i;

	config = 0;
	while (get_next_line(fd, &line) == 1)
		ft_lstadd_back(&config, ft_lstnew(line));
	arr = (char**)malloc(sizeof(char*) * (ft_lstsize(config) + 1));
	if (!arr)
	{
		ft_putendl_fd("Error", 2);
		exit(3);
	}
	i = 0;
	while (config)
	{
		arr[i] = config->content;
		i++;
		config = config->next;
	}
	ft_lstclear(&config, 0);
	arr[i] = 0;
	return (arr);
}

static int	is_texture_config(char *str)
{
	return (ft_strncmp(str, "NO ", 3) == 0 ||
			ft_strncmp(str, "SO ", 3) == 0 ||
			ft_strncmp(str, "WE ", 3) == 0 ||
			ft_strncmp(str, "EA ", 3) == 0 ||
			ft_strncmp(str, "S ", 2) == 0);
}
//todo: handle 0 width and so on
static void render_size_parse(t_mlx *mlx_info, char *str)
{
	int i;

	i = 2;
	while (str[i] == ' ')
		i++;
	mlx_info->width = ft_atoi(str + i);
	i += ft_nbrlen(mlx_info->width);
	if (mlx_info->window && mlx_info->width > 2560)
		mlx_info->width = 2560;
	while (str[i] == ' ')
		i++;
	mlx_info->height = ft_atoi(str + i);
	if (mlx_info->window && mlx_info->height > 1440)
		mlx_info->height = 1440;
	free(str);
}

static void	new_texture(t_mlx *mlx_info, t_img *texture, char *file)
{
	texture->img = mlx_xpm_file_to_image(mlx_info->init, file, &texture->width, &texture->height);
	if (texture->img == 0)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		perror(0);
		exit(2);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

static void texture_parse(t_mlx *mlx_info, char *str)
{
	int i;

	i = 2;
	while (str[i] == ' ')
		i++;
	if (ft_strncmp(str, "NO", 2) == 0)
		new_texture(mlx_info, &mlx_info->north_texture, str + i);
	else if (ft_strncmp(str, "SO", 2) == 0)
		new_texture(mlx_info, &mlx_info->south_texture, str + i);
	else if (ft_strncmp(str, "WE", 2) == 0)
		new_texture(mlx_info, &mlx_info->west_texture, str + i);
	else if (ft_strncmp(str, "EA", 2) == 0)
		new_texture(mlx_info, &mlx_info->east_texture, str + i);
	else if (ft_strncmp(str, "S ", 2) == 0)
		new_texture(mlx_info, &mlx_info->sprite_texture, str + i);
	free(str);
}

static void	color_parse(t_mlx *mlx_info, const char *str)
{
	int i;
	char **arr;
	int color;

	i = 2;
	while (str[i] == ' ')
		i++;
	arr = ft_split(str + i, ',');
	i = 0;
	while (arr[i] != 0)
		i++;
	if (i != 3)
	{
		ft_putendl_fd("Error", 2);
		exit(2);
	}
	color = (ft_atoi(arr[0]) << 16) | (ft_atoi(arr[1]) << 8) |
			(ft_atoi(arr[2]) << 0);
	if (ft_strncmp(str, "F ", 2) == 0)
		mlx_info->floor_color = color;
	else
		mlx_info->ceiling_color = color;
	while (i-- < 3)
		free(arr[i]);
	free(arr);
}

void	read_sprites(t_mlx *mlx_info, char **map)
{
	int i;
	int j;
	int k;

	mlx_info->sprites = (t_sprite*)ft_calloc(mlx_info->sprites_count, sizeof(t_sprite));
	i = 0;
	k = 0;
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

int		check_map(t_mlx *mlx_info, char **map)
{
	int len;
	int i;
	int j;

	len = 0;
	while (map[len] != 0)
		len++;
	mlx_info->map_height = len;
	mlx_info->map_width = 0;
	i = 0;
	while (map[i] != 0)
	{
		j = 0;
		len = (int)ft_strlen(map[i]);
		if (len > mlx_info->map_width)
			mlx_info->map_width = len;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				mlx_info->player.position.x = (float)j * 50.f + 25.f;
				mlx_info->player.position.y = (float)i * 50.f + 25.f;
				if (map[i][j] == 'N')
					mlx_info->player.angle = 90.f;
				else if (map[i][j] == 'S')
					mlx_info->player.angle = -90.f;
				else if (map[i][j] == 'W')
					mlx_info->player.angle = 180.f;
				else
					mlx_info->player.angle = 0.f;
				map[i][j] = '0';
			}
			if (map[i][j] == '2')
				mlx_info->sprites_count++;
			j++;
		}
		i++;
	}
	read_sprites(mlx_info, map);
	return (1);
}

void	map_copy(t_mlx *mlx_info, char **arr)
{
	int i;

	if (!check_map(mlx_info, arr))
	{
		ft_putendl_fd("Error", 2);
		exit(2);
	}
	i = 0;
	while (arr[i] != 0)
		i++;
	mlx_info->map = (char**)malloc(sizeof(char*) * (i + 1));
	if (!mlx_info->map)
	{
		ft_putendl_fd("Error", 2);
		exit(2);
	}
	i = 0;
	while (arr[i] != 0)
	{
		mlx_info->map[i] = arr[i];
		i++;
	}
	mlx_info->map[i] = 0;
}

void	parse_config(t_mlx *mlx_info, char *file)
{
	int fd;
	char **config;
	int i;
	int count;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		perror(file);
		exit(2);
	}
	config = read_config(fd);
	i = 0;
	count = 0;
	while (config[i] != 0)
	{
		if (count == 8)
		{
			while (config[i][0] == '\0')
				i++;
			map_copy(mlx_info, config + i);
			break ;
		}
		count++;
		if (ft_strncmp(config[i], "R ", 2) == 0)
			render_size_parse(mlx_info, config[i]);
		else if (is_texture_config(config[i]))
			texture_parse(mlx_info, config[i]);
		else if (ft_strncmp(config[i], "F ", 2) == 0 ||
				 ft_strncmp(config[i], "C ", 2) == 0)
			color_parse(mlx_info, config[i]);
		else
		{
			free(config[i]);
			count--;
		}
		i++;
	}
	free(config);
	close(fd);
}
