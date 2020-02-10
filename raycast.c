/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:10:46 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/07 15:34:23 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_tex_x(t_cub *cub)
{
	double wallx;

	if (cub->side_hit)
		wallx = cub->p_x + cub->d_wall * cub->rdir_x;
	else
		wallx = cub->p_y + cub->d_wall * cub->rdir_y;
	wallx -= floor(wallx);
	cub->text[cub->hit - 1].tex_x = (int)(wallx *
	(double)cub->text[cub->hit - 1].width);
	if (cub->side_hit == 0 && cub->rdir_x > 0)
		cub->text[cub->hit - 1].tex_x = cub->text[cub->hit - 1].width
		- cub->text[cub->hit - 1].tex_x - 1;
	if (cub->side_hit == 1 && cub->rdir_y < 0)
		cub->text[cub->hit - 1].tex_x = cub->text[cub->hit - 1].width
		- cub->text[cub->hit - 1].tex_x - 1;
}

void	init_side(t_cub *cub)
{
	if (cub->rdir_x < 0)
	{
		cub->nx = -1;
		cub->d_sidex = (cub->p_x - cub->rp_x) * cub->d_deltax;
	}
	else
	{
		cub->nx = 1;
		cub->d_sidex = (cub->rp_x + 1.0 - cub->p_x) * cub->d_deltax;
	}
	if (cub->rdir_y < 0)
	{
		cub->ny = -1;
		cub->d_sidey = (cub->p_y - cub->rp_y) * cub->d_deltay;
	}
	else
	{
		cub->ny = 1;
		cub->d_sidey = (cub->rp_y + 1.0 - cub->p_y) * cub->d_deltay;
	}
}

void	calc_cast(t_cub *cub)
{
	init_side(cub);
	while (cub->hit == 0)
	{
		if (cub->d_sidex < cub->d_sidey)
		{
			cub->d_sidex += cub->d_deltax;
			cub->rp_x += cub->nx;
			cub->side_hit = 0;
		}
		else
		{
			cub->d_sidey += cub->d_deltay;
			cub->rp_y += cub->ny;
			cub->side_hit = 1;
		}
		if (cub->tab->sm[cub->rp_y][cub->rp_x] == '1')
			cub->hit = wall_hit(cub);
	}
}

double	iray(t_cub *cub, int x)
{
	cub->side_s = 2 * x / (double)cub->w_w - 1;
	cub->rdir_x = cub->d_x + cub->plane_x * cub->side_s;
	cub->rdir_y = cub->d_y + cub->plane_y * cub->side_s;
	cub->rp_x = cub->p_x;
	cub->rp_y = cub->p_y;
	cub->d_deltax = fabs(1 / cub->rdir_x);
	cub->d_deltay = fabs(1 / cub->rdir_y);
	cub->hit = 0;
	calc_cast(cub);
	if (cub->side_hit == 0)
		cub->d_wall = (cub->rp_x - cub->p_x + (1 - cub->nx) / 2) / cub->rdir_x;
	else if (cub->side_hit == 1)
		cub->d_wall = (cub->rp_y - cub->p_y + (1 - cub->ny) / 2) / cub->rdir_y;
	cub->line_height = cub->w_h / cub->d_wall;
	cub->dw_start = -cub->line_height / 2 + cub->w_h / 2;
	if (cub->dw_start < 0)
		cub->dw_start = 0;
	cub->dw_end = cub->line_height / 2 + cub->w_h / 2;
	calc_tex_x(cub);
	cub->step = 1.0 * cub->text[cub->hit - 1].height / cub->line_height;
	cub->texpos = (cub->dw_start - cub->w_h /
	2 + cub->line_height / 2) * cub->step;
	if (cub->dw_end >= cub->w_h)
		cub->dw_end = cub->w_h - 1;
	return (cub->step);
}

int		raycast(t_cub *cub)
{
	double zbuffer[cub->w_w];

	cub->x = -1;
	if (!load_texture(cub))
		return (0);
	while (++cub->x < (cub->l_size / 4) && (cub->step = iray(cub, cub->x)))
	{
		cub->y = -1;
		while (++cub->y < cub->dw_start)
			*(int *)(cub->img + cub->y * cub->l_size + cub->x * 4) =
			cub->ceil[0] * 65536 + cub->ceil[1] * 256 + cub->ceil[2];
		cub->y = cub->dw_start;
		while (cub->y++ < cub->dw_end)
			draw_text(cub, cub->y, cub->x, cub->step);
		while (cub->y < cub->w_h)
			*(int *)(cub->img + cub->y++ * cub->l_size + cub->x * 4) =
			cub->floor[0] * 65536 + cub->floor[1] * 256 + cub->floor[2];
		zbuffer[cub->x] = cub->d_wall;
	}
	if (display_sprite(cub, zbuffer) && !cub->save)
		mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->ptr_img, 0, 0);
	return (1);
}
