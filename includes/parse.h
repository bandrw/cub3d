/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:12:42 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/05 20:12:43 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"

int			parse_map(t_mlx *mlx_info, char **map);
int			point_exists(t_mlx *mlx_info, char **map, int x, int y);
int			normalize_map(t_mlx *mlx_info, char **map);
void		read_sprites(t_mlx *mlx_info, char **map);
t_list		*new_point(int x, int y);
void		new_texture(t_mlx *mlx_info, t_img *texture, char *file);
void		parse_color(t_mlx *mlx_info, const char *str);
void		parse_texture(t_mlx *mlx_info, char *str);
void		parse_render_size(t_mlx *mlx_info, char *str);

#endif
