/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:46:24 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/07 15:46:57 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_text(t_cub *cub, int y, int x, double step)
{
	int walltex;

	cub->text[cub->hit - 1].tex_y = (int)cub->texpos;
	cub->texpos += step;
	walltex = cub->text[cub->hit - 1].tex_x % cub->text[cub->hit - 1].width * 4
				+ cub->text[cub->hit - 1].tex_y % cub->text[cub->hit - 1].height
				* cub->text[cub->hit - 1].s_line;
	ft_memcpy(&cub->img[(cub->w_w * y + x) * 4],
	&cub->text[cub->hit - 1].str[walltex], sizeof(int));
}

void	draw_sprite(t_cub *cub, int y, int x)
{
	int walltex;

	walltex = cub->text[4].tex_x % cub->text[4].width * 4
				+ cub->text[4].tex_y % cub->text[4].height
				* cub->text[4].s_line;
	if (cub->text[4].str[walltex] != 0)
		ft_memcpy(&cub->img[(cub->w_w * y + x) * 4],
		&cub->text[4].str[walltex], sizeof(int));
}
