#include "cub3d.h"
#include "bonus.h"

static float	get_angle_diff(float a1, float a2)
{
	if (cosf(to_rad(a2)) > 0 || cosf(to_rad(a1)) > 0)
		return (a2 - a1);
	if (a1 > 114.f && a2 < 0)
		return (a2 + 360.f - a1);
	if (a1 < -114.f && a2 > 0)
		return (a2 - (a1 + 360.f));
	return (a2 - a1);
}

static void		put_sprite(t_mlx *mlx_info, t_pointf trick, t_point start,
							  const float lengths[mlx_info->width])
{
	int				i;
	int				j;
	unsigned int	color;

	i = -1;
	while ((float)++i < trick.x)
	{
		if (i + start.x >= 0 && i + start.x < mlx_info->width &&
			trick.y <= lengths[i + start.x])
		{
			j = -1;
			if (start.y < 0)
				j = (int)((trick.x - (float)mlx_info->height) / 2.f);
			while ((float)++j < trick.x && j + start.y < mlx_info->height)
			{
				color = img_get_pixel(&mlx_info->sprite_texture, i *
					(mlx_info->sprite_texture.width / trick.x),
					j * (mlx_info->sprite_texture.height / trick.x));
				if (color != 0xFF000000)
					color = to_dark(color, trick.x);
				if (color != 0xFF000000)
					img_pixel_put(&mlx_info->stage, i + start.x, j + start.y,
								  color);
			}
		}
	}
}

static void		draw_sprite(t_mlx *mlx_info, float length, float sprite,
							   const float lengths[mlx_info->width])
{
	float		size;
	t_point		start;
	t_pointf	trick;

	if (fabsf(get_angle_diff(mlx_info->player.angle, sprite)) > 66.f ||
		fabsf(cosf(to_rad(mlx_info->player.angle - sprite))) < 0.001f)
		return ;
	size = 40.f * (float)mlx_info->width / length;
	start.x = (int)((get_angle_diff(sprite, mlx_info->player.angle) + 33.f) /
					66.f * (float)mlx_info->width - size / 2.f);
	if (size + (float)start.x < 0 || start.x > mlx_info->width)
		return ;
	size /= cosf(to_rad(get_angle_diff(mlx_info->player.angle, sprite)));
	start.x = (int)((get_angle_diff(sprite, mlx_info->player.angle) + 33.f) /
					66.f * (float)mlx_info->width - size / 2.f);
	start.y = (mlx_info->height - (int)size) / 2;
	trick.x = size;
	trick.y = length;
	put_sprite(mlx_info, trick, start, lengths);
}

static void		sort_sprites(t_mlx *mlx_info)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < mlx_info->sprites_count)
	{
		j = i + 1;
		while (j < mlx_info->sprites_count)
		{
			if (mlx_info->sprites[i].length < mlx_info->sprites[j].length)
			{
				tmp = mlx_info->sprites[i];
				mlx_info->sprites[i].x_index = mlx_info->sprites[j].x_index;
				mlx_info->sprites[i].y_index = mlx_info->sprites[j].y_index;
				mlx_info->sprites[i].length = mlx_info->sprites[j].length;
				mlx_info->sprites[j].x_index = tmp.x_index;
				mlx_info->sprites[j].y_index = tmp.y_index;
				mlx_info->sprites[j].length = tmp.length;
			}
			j++;
		}
		i++;
	}
}

void			put_sprites(t_mlx *mlx_info,
							const float lengths[mlx_info->width])
{
	int		i;
	float	sprite;

	i = -1;
	while (++i < mlx_info->sprites_count)
		mlx_info->sprites[i].length = sqrtf(powf(
				(float)mlx_info->sprites[i].x_index * 50.f + 25.f -
				mlx_info->player.position.x, 2) +
											powf((float)mlx_info->sprites[i].y_index * 50.f + 25.f -
												 mlx_info->player.position.y, 2));
	i = -1;
	sort_sprites(mlx_info);
	while (++i < mlx_info->sprites_count)
	{
		sprite = to_deg(atan2f(mlx_info->player.position.y -
							   (float)mlx_info->sprites[i].y_index * 50.f - 25.f,
							   (float)mlx_info->sprites[i].x_index * 50.f -
							   mlx_info->player.position.x + 25.f));
		draw_sprite(mlx_info, mlx_info->sprites[i].length, sprite, lengths);
	}
}
