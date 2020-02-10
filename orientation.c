/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:34:58 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/07 15:36:31 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	p_orient0(t_cub *cub)
{
	if (cub->p_v == 'W')
	{
		cub->d_x = -1;
		cub->d_y = 0;
		cub->plane_x = 0;
		cub->plane_y = -0.66;
	}
	else if (cub->p_v == 'E')
	{
		cub->d_x = 1;
		cub->d_y = 0;
		cub->plane_x = 0;
		cub->plane_y = 0.66;
	}
}

void	p_orient(t_cub *cub)
{
	if (cub->p_v == 'W' || cub->p_v == 'E')
		p_orient0(cub);
	else if (cub->p_v == 'S')
	{
		cub->d_x = 0;
		cub->d_y = 1;
		cub->plane_x = -0.66;
		cub->plane_y = 0;
	}
	else if (cub->p_v == 'N')
	{
		cub->d_x = 0;
		cub->d_y = -1;
		cub->plane_x = 0.66;
		cub->plane_y = 0;
	}
}
