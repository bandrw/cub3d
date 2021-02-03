#ifndef BMP_H
# define BMP_H

typedef struct		s_bmp_header
{
	unsigned int	size;
	unsigned int	reserved_bytes;
	unsigned int	pixel_data_offset;
	unsigned int	header_size;
	int				width;
	int				height;
	unsigned short	color_planes;
	unsigned short	color_depth;
	unsigned int	compression_method;
	unsigned int	raw_bitmap_data_size;
	int				horizontal_resolution;
	int				vertical_resolution;
	unsigned int	color_table_entries;
	unsigned int	important_colors;
}					t_bmp_header;

typedef struct		s_pixel
{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
}					t_pixel;

#endif
