#include "bonus.h"

int				img_pixel_put(t_img *img_data, int x, int y, unsigned int color)
{
	char *dst;

	if (x >= img_data->width || x < 0 || y >= img_data->height || y < 0)
		return (1);
	dst = img_data->addr + (y * img_data->line_length + x *
														(img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	return (0);
}

unsigned int	img_get_pixel(t_img *img_data, int x, int y)
{
	char *dst;

	dst = img_data->addr + (y * img_data->line_length + x *
														(img_data->bits_per_pixel / 8));
	if (dst)
		return (*(int*)dst);
	return (0);
}

void			put_rectangle(t_img *img_data, t_rectangle *rectangle,
							  int color)
{
	int start_x;
	int start_y;
	int i;
	int j;

	start_x = (int)rectangle->start.x;
	start_y = (int)rectangle->start.y;
	i = start_x;
	while (i < start_x + rectangle->width)
	{
		j = start_y;
		while (j < start_y + rectangle->height)
		{
			if (i >= 0 && j >= 0 && i < img_data->width && j < img_data->height)
				img_pixel_put(img_data, i, j, color);
			j++;
		}
		i++;
	}
}

void			put_ceilling_and_floor(t_mlx *mlx_info)
{
	t_rectangle rectangle;

	rectangle.width = mlx_info->width;
	rectangle.height = mlx_info->height / 2;
	rectangle.start.x = 0;
	rectangle.start.y = 0;
	put_rectangle(&mlx_info->stage, &rectangle, mlx_info->ceiling_color);
	rectangle.start.y = (float)mlx_info->height / 2.f;
	put_rectangle(&mlx_info->stage, &rectangle, mlx_info->floor_color);
}
