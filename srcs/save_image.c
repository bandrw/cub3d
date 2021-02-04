#include "cub3d.h"

static void		bmp_init(t_mlx *mlx_info, t_bmp_header *bmp_header)
{
	bmp_header->size = 54 + mlx_info->width * mlx_info->height * 3;
	bmp_header->reserved_bytes = 0;
	bmp_header->pixel_data_offset = 54;
	bmp_header->header_size = 40;
	bmp_header->width = mlx_info->width;
	bmp_header->height = mlx_info->height;
	bmp_header->color_planes = 1;
	bmp_header->color_depth = 3 * 8;
	bmp_header->compression_method = 0;
	bmp_header->raw_bitmap_data_size = 0;
	bmp_header->horizontal_resolution = 3780;
	bmp_header->vertical_resolution = 3780;
	bmp_header->color_table_entries = 0;
	bmp_header->important_colors = 0;
}

void			save_image(t_mlx *mlx_info, char *out_file)
{
	int				i;
	int				j;
	int				fd;
	t_pixel			pixel[mlx_info->width];
	unsigned int	color;
	t_bmp_header	bmp_header;

	fd = open(out_file, O_CREAT | O_WRONLY | O_TRUNC, S_IWRITE);
	if (fd == -1)
		throw_error("File output error");
	bmp_init(mlx_info, &bmp_header);
	write(fd, "BM", 2);
	write(fd, &bmp_header, sizeof(bmp_header));
	main_render(mlx_info);
	i = bmp_header.height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < bmp_header.width)
		{
			color = img_get_pixel(&mlx_info->stage, j, i);
			pixel[j].red = color >> (unsigned int)16;
			pixel[j].green = color >> (unsigned int)8;
			pixel[j].blue = color >> (unsigned int)0;
			j++;
		}
		write(fd, pixel, sizeof(t_pixel) * mlx_info->width);
		i--;
	}
	close(fd);
}
