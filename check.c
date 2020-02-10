/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:26:25 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/07 17:28:08 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*take_path(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (&str[i]);
}

int		check_elem(t_cub *cub, int y)
{
	int i;
	int v;

	i = 0;
	v = -1;
	while (i < y)
	{
		if (!cub->w_w || !cub->w_h)
			return (0);
		i++;
		while (cub->file.path[++v] != NULL)
			i++;
		if (y != i && i < 5)
			return (0);
		if (cub->floor[3] == 1)
			i++;
		if (y != i)
			return (0);
	}
	return (1);
}

int		floor_ceilur(t_cub *cub, int i)
{
	if (cub->file.line[0] == 'F' && check_elem(cub, 6))
	{
		if (!guess_color(cub, i, cub->floor))
			return (0);
	}
	else if (cub->file.line[0] == 'C' && check_elem(cub, 7))
	{
		if (!guess_color(cub, i, cub->ceil))
			return (0);
	}
	else
		return (0);
	return (1);
}

int		check_letter(t_cub *cub)
{
	int i;

	i = 2;
	if (cub->file.line[0] == 'R' && check_elem(cub, 0))
	{
		if (!guess_wnh(cub, i))
			return (0);
	}
	else if (cub->file.line[0] == 'N' && cub->file.line[1] == 'O'
	&& check_elem(cub, 1))
		cub->file.path[0] = take_path(&cub->file.line[3]);
	else if (cub->file.line[0] == 'S' && cub->file.line[1] == 'O'
	&& check_elem(cub, 2))
		cub->file.path[1] = take_path(&cub->file.line[3]);
	else if (cub->file.line[0] == 'W' && cub->file.line[1] == 'E'
	&& check_elem(cub, 3))
		cub->file.path[2] = take_path(&cub->file.line[3]);
	else if (cub->file.line[0] == 'E' && cub->file.line[1] == 'A'
	&& check_elem(cub, 4))
		cub->file.path[3] = take_path(&cub->file.line[3]);
	else if (cub->file.line[0] == 'S' && check_elem(cub, 5))
		cub->file.path[4] = take_path(&cub->file.line[3]);
	else if (!floor_ceilur(cub, i))
		return (0);
	return (1);
}

int		check_file(int fd, t_cub *cub)
{
	int i;

	i = -1;
	while (get_next_line(fd, &cub->file.line) && cub->file.line[0] != '1')
	{
		if (!check_letter(cub) && cub->file.line[0] != '\0')
			return (error("Error in resolution/texture/ceiling/floor writing",
			cub));
	}
	while (++i < 4)
		if (cub->file.path[i] == NULL)
			return (error("Not every way given", cub));
	if (cub->floor[3] == 0 || cub->ceil[3] == 0)
		return (error("Ceil or floor not given", cub));
	return (1);
}
