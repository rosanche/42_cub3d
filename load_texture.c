/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:37:20 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/07 15:37:50 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		load_texture(t_cub *cub)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (cub->file.path[i] != NULL)
		{
			cub->text[i].ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->file.path[i], &cub->text[i].width, &cub->text[i].height);
			if (cub->text[i].ptr == NULL)
				return (error("Wrong path file", cub));
			cub->text[i].str = mlx_get_data_addr(cub->text[i].ptr,
			&cub->text[i].bpp, &cub->text[i].s_line, &cub->text[i].endian);
		}
		i++;
	}
	return (1);
}
