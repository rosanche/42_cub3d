/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guess.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:28:23 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/10 15:28:25 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		guess_wnh(t_cub *cub, int i)
{
	while (cub->file.line[i] == ' ')
		i++;
	if (ft_isdigit(cub->file.line[i]))
		cub->w_w = ft_atoi(&cub->file.line[i]);
	else
		return (0);
	while (ft_isdigit(cub->file.line[i]))
		i++;
	while (cub->file.line[i] == ' ')
		i++;
	if (ft_isdigit(cub->file.line[i]))
		cub->w_h = ft_atoi(&cub->file.line[i]);
	else
		return (0);
	while (ft_isdigit(cub->file.line[i]))
		i++;
	cub->w_w = cub->w_w > 2560 ? 2560 : cub->w_w;
	cub->w_h = cub->w_h > 1440 ? 1440 : cub->w_h;
	return (!cub->file.line[i] ? 1 : 0);
}

int		guess_color(t_cub *cub, int i, int *floor)
{
	int v;

	v = -1;
	while (++v < 3)
	{
		while (cub->file.line[i] == ' ' && cub->file.line[i])
			i++;
		if (ft_isdigit(cub->file.line[i]) && cub->file.line[i])
			floor[v] = ft_atoi(&cub->file.line[i]);
		else
			return (0);
		while (ft_isdigit(cub->file.line[i]) && cub->file.line[i])
			i++;
		while (cub->file.line[i] == ' ' && v < 2)
			i++;
		if (cub->file.line[i] != ',' && v < 2)
			return (0);
		while (cub->file.line[i] == ' ' && v < 2)
			i++;
		if (floor[v] > 255)
			return (0);
		i++;
	}
	floor[3] = 1;
	return (!cub->file.line[i - 1] ? 1 : 0);
}
