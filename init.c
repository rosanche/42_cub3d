/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:41:10 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/07 15:41:12 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_gril	*init_s(t_gril *tab)
{
	if (!(tab = (t_gril *)malloc(sizeof(t_gril))))
		return (NULL);
	if (!(tab->sm = (char**)malloc(sizeof(char *) * 1000)))
		return (NULL);
	tab->map_width = 0;
	tab->map_height = 0;
	return (tab);
}

t_cub	*init_cub(t_cub *cub)
{
	if (!(cub = (t_cub *)malloc(sizeof(t_cub))))
		return (NULL);
	cub->w_h = 0;
	cub->w_w = 0;
	cub->p_x = -1;
	cub->p_y = -1;
	cub->p_v = '\0';
	cub->d_x = -1;
	cub->d_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0.66;
	cub->nb_sprite = 0;
	cub->tab = init_s(cub->tab);
	return (cub);
}
