/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:42:04 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/10 15:28:44 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_game(t_cub *cub, int fd)
{
	if (!check_file(fd, cub))
		return (-1);
	if (!height_n_fill(fd, cub, cub->file.line))
		return (error("Problem with your map", cub));
	if (!width(cub->tab, cub))
		return (error("Problem with your map", cub));
	if (!check_map(cub))
		return (-1);
	p_orient(cub);
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr,
	cub->w_w, cub->w_h, "Cub3D");
	if (!(cub->ptr_img = mlx_new_image(cub->mlx_ptr, cub->w_w, cub->w_h)))
		return (0);
	cub->img = mlx_get_data_addr(cub->ptr_img, &cub->bt, &cub->l_size, &cub->e);
	if (!(raycast(cub)))
		return (-1);
	mlx_hook(cub->win_ptr, 2, 0, press_key, (void *)cub);
	mlx_hook(cub->win_ptr, 3, 0, release_key, (void *)cub);
	mlx_hook(cub->win_ptr, 17, 0, stop, (void *)cub);
	mlx_loop_hook(cub->mlx_ptr, deal_key, (void *)cub);
	mlx_do_key_autorepeatoff(cub->mlx_ptr);
	mlx_loop(cub->mlx_ptr);
	destroy(cub);
	return (0);
}

int	save_game(t_cub *cub, int fd)
{
	if (!check_file(fd, cub))
		return (-1);
	if (!height_n_fill(fd, cub, cub->file.line))
		return (error("Problem with your map", cub));
	if (!width(cub->tab, cub))
		return (error("Problem with your map", cub));
	ft_putendl("filled width");
	if (!check_map(cub))
		return (-1);
	ft_putendl("filled and check");
	p_orient(cub);
	ft_putendl("filled and check");
	cub->mlx_ptr = mlx_init();
	cub->save = true;
	ft_putendl("window opened");
	if (!(raycast(cub)))
		return (-1);
	return (0);
}
