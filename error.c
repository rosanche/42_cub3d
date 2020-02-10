/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:45:38 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/10 15:29:06 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		error(char *str, t_cub *cub)
{
	if (cub != NULL)
	{
		ft_strdel(cub->tab->sm);
		free(cub->tab);
		free(cub->s);
		free(cub->dt_sprite);
		free(cub->or_sprite);
		free(cub);
	}
	ft_putendl("Error");
	ft_putendl(str);
	return (0);
}

int		stop(t_cub *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->ptr_img);
	ft_strdel(cub->tab->sm);
	free(cub->tab);
	free(cub->s);
	free(cub->dt_sprite);
	free(cub->or_sprite);
	free(cub);
	exit(0);
	return (0);
}

void	destroy(t_cub *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->ptr_img);
	ft_strdel(cub->tab->sm);
	free(cub->tab);
	free(cub->s);
	free(cub->dt_sprite);
	free(cub->or_sprite);
	free(cub);
	exit(0);
}
