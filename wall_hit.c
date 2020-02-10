/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:54:03 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/06 18:55:00 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		wall_hit(t_cub *cub)
{
	if (cub->p_x < cub->rp_x && cub->side_hit == 0)
		cub->hit = 4;
	else if (cub->p_x > cub->rp_x && cub->side_hit == 0)
		cub->hit = 3;
	else if (cub->side_hit == 1 && cub->p_y > cub->rp_y)
		cub->hit = 1;
	else
		cub->hit = 2;
	return (cub->hit);
}
