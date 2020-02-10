/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:13:08 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/07 14:28:16 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_sprite(t_sprite sprite)
{
	sprite.spritex = 0;
	sprite.spritey = 0;
	sprite.invdet = 0;
	sprite.transformx = 0;
	sprite.transformy = 0;
	sprite.spritescreenx = 0;
	sprite.spritewidth = 0;
	sprite.spriteheight = 0;
	sprite.drawstarty = 0;
	sprite.drawendy = 0;
	sprite.drawstartx = 0;
	sprite.drawendx = 0;
}

t_sprite	get_values(t_sprite s, t_cub *cub)
{
	s.spritex = s.x - cub->p_x;
	s.spritey = s.y - cub->p_y;
	s.invdet = 1.0 / (cub->plane_x * cub->d_y - cub->d_x * cub->plane_y);
	s.transformx = s.invdet * (cub->d_y * s.spritex - cub->d_x * s.spritey);
	s.transformy = s.invdet * (cub->plane_y * -1
	* s.spritex + cub->plane_x * s.spritey);
	s.spritescreenx = (int)(cub->w_w / 2) *
	(1 + s.transformx / s.transformy);
	s.spriteheight = fabs(cub->w_h / (s.transformy));
	s.drawstarty = -s.spriteheight / 2 + cub->w_h / 2;
	if (s.drawstarty < 0)
		s.drawstarty = 0;
	s.drawendy = s.spriteheight / 2 + cub->w_h / 2;
	if (s.drawendy >= cub->w_h)
		s.drawendy = cub->w_h - 1;
	s.spritewidth = fabs(cub->w_h / (s.transformy));
	s.drawstartx = -s.spritewidth / 2 + s.spritescreenx;
	if (s.drawstartx < 0)
		s.drawstartx = 0;
	s.drawendx = s.spritewidth / 2 + s.spritescreenx;
	if (s.drawendx >= cub->w_w)
		s.drawendx = cub->w_w - 1;
	return (s);
}

void		prep_sprite(t_sprite s, t_cub *cub, double *zbuffer)
{
	int		x;
	int		y;
	int		d;

	s = get_values(s, cub);
	x = s.drawstartx;
	while (x < s.drawendx)
	{
		if (s.transformy > 0 && x > 0 && x < cub->w_h
			&& s.transformy < zbuffer[x])
		{
			cub->text[4].tex_x = (int)(256 * (x - (-s.spritewidth / 2
			+ s.spritescreenx)) * cub->text[4].width / s.spritewidth) / 256;
			y = s.drawstarty;
			while (y < s.drawendy)
			{
				d = (y) * 256 - cub->w_h * 128 + s.spriteheight * 128;
				cub->text[4].tex_y = ((d * cub->text[4].height)
				/ s.spriteheight) / 256;
				draw_sprite(cub, y, x);
				y++;
			}
		}
		x++;
	}
}

void		sort_sprite(t_cub *cub)
{
	int		i;
	int		j;
	double	max;
	int		save;

	i = 0;
	while (i < cub->nb_sprite)
	{
		j = i;
		max = cub->dt_sprite[cub->or_sprite[i]];
		while (j < cub->nb_sprite)
		{
			if (cub->dt_sprite[cub->or_sprite[j]] > max)
			{
				max = cub->dt_sprite[cub->or_sprite[j]];
				save = cub->or_sprite[j];
				cub->or_sprite[j] = cub->or_sprite[i];
				cub->or_sprite[i] = save;
			}
			j++;
		}
		i++;
	}
}

int			display_sprite(t_cub *cub, double *zbuffer)
{
	int		i;
	int		n;

	i = 0;
	while (i < cub->nb_sprite)
	{
		cub->or_sprite[i] = i;
		cub->dt_sprite[i] = ((cub->p_x - (cub->s[i].x)) *
		(cub->p_x - (cub->s[i].x)) + (cub->p_y - (cub->s[i].y))
		* (cub->p_y - (cub->s[i].y)));
		i++;
	}
	sort_sprite(cub);
	i = 0;
	while (i < cub->nb_sprite)
	{
		n = cub->or_sprite[i];
		init_sprite(cub->s[n]);
		prep_sprite(cub->s[n], cub, zbuffer);
		i++;
	}
	return (1);
}
