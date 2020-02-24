/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:58:10 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/07 17:21:52 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_value(t_cub *cub, char c, int i, int count)
{
	if (c == '2')
	{
		cub->s[cub->nb_sprite].y = (double)count + 0.5;
		cub->s[cub->nb_sprite].x = (double)i + 0.5;
		cub->nb_sprite++;
	}
	else if (c != '1' && c != '0' && c != '2' && c != 'N' && c != 'S'
	&& c != 'W' && c != 'E')
		return (error("Problem with your map", cub));
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (cub->p_v)
			return (error("Too many player positions", cub));
		cub->p_v = c;
		cub->p_x = i + 0.5;
		cub->p_y = count + 0.5;
	}
	return (1);
}

int		get_pos(t_cub *cub, int count, int end)
{
	int		i;
	char	c;

	if ((int)ft_strlen(cub->tab->sm[count]) != cub->tab->map_width)
		return (error("Not the same width everywhere in your map", cub));
	if (cub->tab->sm[count][0] != '1' || cub->tab->sm[count][end] != '1')
		return (error("Your map is not surrounded by walls", cub));
	i = 0;
	while (cub->tab->sm[count][i])
	{
		c = cub->tab->sm[count][i];
		if (!get_value(cub, c, i, count))
			return (0);
		i++;
	}
	return (1);
}

int		check_map(t_cub *cub)
{
	int		c;
	int		end;

	if (!(cub->s = (t_sprite *)malloc(sizeof(t_sprite) * (cub->nb_sprite + 1))))
		return (-1);
	if (!(cub->dt_sprite = (double *)malloc(sizeof(double)
	* (cub->nb_sprite + 1))))
		return (-1);
	if (!(cub->or_sprite = (int *)malloc(sizeof(int) * (cub->nb_sprite + 1))))
		return (-1);
	ft_bzero(cub->s, sizeof(t_sprite *) * cub->nb_sprite + 1);
	ft_bzero(cub->dt_sprite, sizeof(int) * (cub->nb_sprite + 1));
	ft_bzero(cub->or_sprite, sizeof(int) * (cub->nb_sprite + 1));
	cub->nb_sprite = 0;
	c = -1;
	end = cub->tab->map_width - 1;
	while (++c < cub->tab->map_height)
		if (!get_pos(cub, c, end))
			return (0);
	c = -1;
	end = cub->tab->map_height - 1;
	while (++c < cub->tab->map_width)
		if (cub->tab->sm[0][c] != '1' || cub->tab->sm[end][c] != '1')
			return (error("Your map is not surrounded by walls", cub));
	return (1);
}

int		name_check(char *str, t_cub *cub)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
	{
		if ((ft_strcmp(&str[i], ".cub")) != 0)
			return (error("Wrong file name", cub));
		return (1);
	}
	else
		return (error("Wrong file name", cub));
}

int		main(int ac, char **av)
{
	int		fd;
	t_cub	*cub;

	cub = NULL;
	if (ac != 2 && ac != 3)
		return (error("Wrong number of arguments", cub));
	cub = init_cub(cub);
	if (name_check(av[1], cub))
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
			return (error("File didn't open", cub));
		if (ac == 3 && !ft_strcmp(av[2], "--save"))
			return (create_screenshot(cub, fd));
		else if (ac == 2)
			return (start_game(cub, fd));
		else
			return (error("Wrong arguments", cub));
	}
	else
		return (0);
	return (0);
}
