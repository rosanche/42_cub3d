/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:47:33 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/10 15:28:02 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		release_key(int key, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (key == 13)
		cub->move.front = false;
	else if (key == 1)
		cub->move.back = false;
	else if (key == 0)
		cub->move.left = false;
	else if (key == 2)
		cub->move.right = false;
	else if (key == 123)
		cub->move.r_left = false;
	else if (key == 124)
		cub->move.r_right = false;
	return (0);
}

int		press_key(int key, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (key == 13)
		cub->move.front = true;
	else if (key == 1)
		cub->move.back = true;
	else if (key == 0)
		cub->move.left = true;
	else if (key == 2)
		cub->move.right = true;
	else if (key == 123)
		cub->move.r_left = true;
	else if (key == 124)
		cub->move.r_right = true;
	else if (key == 53)
		cub->move.esc = true;
	return (0);
}

void	move(t_cub *cub)
{
	double old_plane;
	double old_d;
	double rots;

	rots = 0.04;
	if (cub->move.r_right)
	{
		old_d = cub->d_y;
		cub->d_y = cub->d_y * cos(-rots) - cub->d_x * sin(-rots);
		cub->d_x = old_d * sin(-rots) + cub->d_x * cos(-rots);
		old_plane = cub->plane_y;
		cub->plane_y = cub->plane_y * cos(-rots) - cub->plane_x * sin(-rots);
		cub->plane_x = old_plane * sin(-rots) + cub->plane_x * cos(-rots);
	}
	if (cub->move.r_left)
	{
		old_d = cub->d_y;
		cub->d_y = cub->d_y * cos(rots) - cub->d_x * sin(rots);
		cub->d_x = old_d * sin(rots) + cub->d_x * cos(rots);
		old_plane = cub->plane_y;
		cub->plane_y = cub->plane_y * cos(rots) - cub->plane_x * sin(rots);
		cub->plane_x = old_plane * sin(rots) + cub->plane_x * cos(rots);
	}
}

void	move_ho(t_cub *cub, double m)
{
	if (cub->move.front)
	{
		if (cub->tab->sm[(int)(cub->p_y + cub->d_y * m)][(int)cub->p_x] != '1')
			cub->p_y += cub->d_y * m;
		if (cub->tab->sm[(int)cub->p_y][(int)(cub->p_x + cub->d_x * m)] != '1')
			cub->p_x += cub->d_x * m;
	}
	if (cub->move.back)
	{
		if (cub->tab->sm[(int)(cub->p_y - cub->d_y * m)][(int)cub->p_x] != '1')
			cub->p_y -= cub->d_y * m;
		if (cub->tab->sm[(int)cub->p_y][(int)(cub->p_x - cub->d_x * m)] != '1')
			cub->p_x -= cub->d_x * m;
	}
	if (cub->move.right)
	{
		if (cub->tab->sm[(int)(cub->p_y + cub->d_x
		* m)][(int)cub->p_x] != '1')
			cub->p_y += cub->d_x * m;
		if (cub->tab->sm[(int)cub->p_y][(int)(cub->p_x - cub->d_y
		* m)] != '1')
			cub->p_x -= cub->d_y * m;
	}
}

int		deal_key(t_cub *cub)
{
	double m;
	double rots;

	rots = 0.05;
	m = 0.07;
	if (cub->move.r_left || cub->move.r_right)
		move(cub);
	if (cub->move.front || cub->move.back || cub->move.right)
		move_ho(cub, m);
	if (cub->move.left)
	{
		if (cub->tab->sm[(int)(cub->p_y - cub->d_x * m)][(int)cub->p_x] != '1')
			cub->p_y -= cub->d_x * m;
		if (cub->tab->sm[(int)cub->p_y][(int)(cub->p_x + cub->d_y * m)] != '1')
			cub->p_x += cub->d_y * m;
	}
	if (cub->move.esc)
		destroy(cub);
	if (!cub->move.esc)
		raycast(cub);
	return (0);
}
