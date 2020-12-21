/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 18:53:02 by kfriese           #+#    #+#             */
/*   Updated: 2020/12/05 18:53:03 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_BOTTOM 125
# define KEY_UP 126
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_ESC 53

# include <math.h>
# include "mlx.h"
# include "libft.h"
#include <stdio.h>

typedef struct	s_point
{
	float		x;
	float		y;
}				t_point;

typedef struct	s_line
{
	t_point		coordinate;
	float		length;
	float		angle;
}				t_line;

typedef struct	s_player
{
	t_point		*position;
	float 		angle;
}				t_player;

typedef struct	s_mlx
{
	void		*init;
	void		*window;
	int			width;
	int			height;
	t_player	*player;
	char		**map;
}				t_mlx;

void	player_move(t_mlx *mlx_info, int key);
void	put_square(t_mlx *mlx_info, t_point p, float size, int color);
void	put_line(t_mlx *mlx_info, t_line *line, int color);
int 	is_moveable(int key);
int 	is_arrow(int key);
void	move(t_mlx *mlx_info, int key, float step);
void	change_direction(t_mlx *mlx_info, int key);
char	**new_map(void);

#endif
