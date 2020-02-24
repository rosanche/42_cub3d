/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:28:46 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/07 14:30:11 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int							create_screenshot(t_cub *cub, int fr)
{
	int						fd;

	save_game(cub, fr);
	fd = open("Cub3D.bmp", O_CREAT | O_RDWR, 416);
	create_bmp(cub, fd);
	destroy(cub);
	return (1);
}

void						get_pixels(t_cub *cub, int fd, int y)
{
	unsigned char			rgb[3];
	int						x;
	const int				max_y = cub->w_h - 1;
	const int				max_x = cub->w_w;
	int						*test;

	test = (int *)cub->img;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			rgb[0] = test[(cub->l_size / 4 * (max_y - y)) + (x)];
			rgb[1] = test[(cub->l_size / 4 * (max_y - y)) + (x)] >> 8;
			rgb[2] = test[(cub->l_size / 4 * (max_y - y)) + (x)] >> 16;
			write(fd, rgb, 3);
			x++;
		}
		y++;
	}
}

unsigned char				*create_file_header(int res_y, int res_x)
{
	int						nb_octet;
	static unsigned char	bmp_file_header[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	int						padding;

	padding = (4 - (res_x * 3) % 4) % 4;
	nb_octet = 14 + 40 + (3 * res_x + padding) * res_y;
	bmp_file_header[0] = (unsigned char)('B');
	bmp_file_header[1] = (unsigned char)('M');
	bmp_file_header[2] = (unsigned char)(nb_octet);
	bmp_file_header[3] = (unsigned char)(nb_octet >> 8);
	bmp_file_header[4] = (unsigned char)(nb_octet >> 16);
	bmp_file_header[5] = (unsigned char)(nb_octet >> 24);
	bmp_file_header[10] = (unsigned char)(54);
	return (bmp_file_header);
}

unsigned char				*create_bitmap_header(int res_y, int res_x)
{
	static unsigned char	bmp_bitmap_header[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	bmp_bitmap_header[0] = (unsigned char)(40);
	bmp_bitmap_header[4] = (unsigned char)(res_x);
	bmp_bitmap_header[5] = (unsigned char)(res_x >> 8);
	bmp_bitmap_header[6] = (unsigned char)(res_x >> 16);
	bmp_bitmap_header[7] = (unsigned char)(res_x >> 24);
	bmp_bitmap_header[8] = (unsigned char)(res_y);
	bmp_bitmap_header[9] = (unsigned char)(res_y >> 8);
	bmp_bitmap_header[10] = (unsigned char)(res_y >> 16);
	bmp_bitmap_header[11] = (unsigned char)(res_y >> 24);
	bmp_bitmap_header[12] = (unsigned char)(1);
	bmp_bitmap_header[14] = (unsigned char)(3 * 8);
	return (bmp_bitmap_header);
}

int							create_bmp(t_cub *cub, int fd)
{
	unsigned char			*file_header;
	unsigned char			*bitmap_header;

	file_header = create_file_header(cub->w_h - 1, cub->w_w);
	bitmap_header = create_bitmap_header(cub->w_h - 1, cub->w_w);
	write(fd, file_header, 14);
	write(fd, bitmap_header, 40);
	get_pixels(cub, fd, 0);
	close(fd);
	return (0);
}
