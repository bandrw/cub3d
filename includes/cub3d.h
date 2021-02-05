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

# include "libft.h"
# include "mlx.h"
# include "bmp.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

typedef enum	e_direction
{
	North,
	East,
	South,
	West
}				t_direction;

typedef struct	s_pointf
{
	float		x;
	float		y;
}				t_pointf;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_rectangle
{
	t_pointf	start;
	int			width;
	int			height;
}				t_rectangle;

typedef struct	s_player
{
	t_pointf	position;
	float		angle;
}				t_player;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_sprite
{
	int			x_index;
	int			y_index;
	float		length;
}				t_sprite;

typedef struct	s_ray
{
	float		length;
	t_pointf	end;
	t_direction	direction;
}				t_ray;

typedef struct	s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left_arrow;
	int			right_arrow;
}				t_keys;

typedef struct	s_mlx
{
	void		*init;
	void		*window;
	int			width;
	int			height;
	t_img		stage;
	t_player	player;
	char		**map;
	t_img		north_texture;
	t_img		south_texture;
	t_img		west_texture;
	t_img		east_texture;
	t_img		sprite_texture;
	int			floor_color;
	int			ceiling_color;
	int			map_width;
	int			map_height;
	t_keys		active_keys;
	int			sprites_count;
	t_sprite	*sprites;
}				t_mlx;

void			new_mlx(t_mlx *mlx_info, char *file, char *title, void *out);
int				close_app(t_mlx *mlx_info);
float			to_rad(float degrees);
float			to_deg(float radians);
int				img_pixel_put(t_img *img_data, int x, int y,
								unsigned int color);
unsigned int	img_get_pixel(t_img *img_data, int x, int y);
void			put_ceilling_and_floor(t_mlx *mlx_info);
void			put_rectangle(t_img *img_data, t_rectangle *rectangle,
								int color);
void			move_forward(t_mlx *mlx_info, float step);
void			move_backward(t_mlx *mlx_info, float step);
void			move_left(t_mlx *mlx_info, float step);
void			move_right(t_mlx *mlx_info, float step);
void			change_direction(t_mlx *mlx_info, int key, float step);
void			ray_cast(t_mlx *mlx_info, t_ray *cast, float angle);
void			parse_config(t_mlx *mlx_info, char *file);
int				usage_error(char *program_name);
void			throw_error(char *message);
void			throw_perror(char *message);
void			main_render(t_mlx *mlx_info);
void			put_sprites(t_mlx *mlx_info,
								const float lengths[mlx_info->width]);
void			save_image(t_mlx *mlx_info, char *out_file);

#endif
