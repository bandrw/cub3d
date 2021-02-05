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

#include "parse.h"

static char	**array_from_list(t_list *config)
{
	int		i;
	char	**arr;
	t_list	*tmp;

	if (!(arr = (char**)malloc(sizeof(char*) * (ft_lstsize(config) + 1))))
		throw_error("Can't allocate map");
	tmp = config;
	i = 0;
	while (tmp)
	{
		arr[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	arr[i] = 0;
	return (arr);
}

static char	**read_file(int fd)
{
	int		n;
	char	*line;
	char	**arr;
	t_list	*config;
	t_list	*tmp;

	config = 0;
	while ((n = get_next_line(fd, &line)))
	{
		if (n == -1)
			throw_error("Can't read config");
		if ((tmp = ft_lstnew(line)) == 0)
			throw_error("Can't create t_list");
		ft_lstadd_back(&config, tmp);
	}
	arr = array_from_list(config);
	ft_lstclear(&config, 0);
	return (arr);
}

static void	map_copy(t_mlx *mlx_info, char **arr)
{
	int i;

	if (parse_map(mlx_info, arr) != 0)
		throw_error("Invalid map");
	if (!(mlx_info->map = (char**)malloc(sizeof(char*) *
			(mlx_info->map_height))))
		throw_error("Can't allocate map");
	i = 0;
	while (arr[i] != 0)
	{
		mlx_info->map[i] = arr[i];
		i++;
	}
}

static int	parse_config_line(t_mlx *mlx_info, char **config, int i)
{
	static int count;

	if (count == 8)
	{
		map_copy(mlx_info, config + i);
		return (count + 1);
	}
	count++;
	if (config[i][0] == 'R')
		parse_render_size(mlx_info, config[i]);
	else if (*config[i] == 'S' ||
				ft_strncmp(config[i], "NO", 2) == 0 ||
				ft_strncmp(config[i], "SO", 2) == 0 ||
				ft_strncmp(config[i], "WE", 2) == 0 ||
				ft_strncmp(config[i], "EA", 2) == 0)
		parse_texture(mlx_info, config[i]);
	else if (config[i][0] == 'F' || config[i][0] == 'C')
		parse_color(mlx_info, config[i]);
	else
		count--;
	free(config[i]);
	return (count);
}

void		parse_config(t_mlx *mlx_info, char *file)
{
	int		i;
	int		fd;
	int		tmp;
	char	**config;

	if ((fd = open(file, O_RDONLY)) == -1)
		throw_perror(file);
	config = read_file(fd);
	close(fd);
	i = 0;
	tmp = 0;
	while (config[i] != 0 && tmp != 9)
	{
		if (config[i][0] == '\0')
			free(config[i]);
		else
			tmp = parse_config_line(mlx_info, config, i);
		i++;
	}
	free(config);
	if (tmp != 9)
		throw_error("Invalid config");
}
