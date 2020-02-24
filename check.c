/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:26:25 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/17 14:43:40 by rosanche         ###   ########.fr       */
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

int		floor_ceilur(t_cub *cub, int i)
{
	if (cub->file.line[0] == 'F' && cub->floor[3] == 0)
	{
		if (!guess_color(cub, i, cub->floor))
			return (0);
	}
	else if (cub->file.line[0] == 'C' && cub->ceil[3] == 0)
	{
		if (!guess_color(cub, i, cub->ceil))
			return (0);
	}
	else
		return (0);
	free(cub->file.line);
	return (1);
}

int		check_letter(t_cub *cub)
{
	if (cub->file.line[0] == 'R' && (cub->w_w || !cub->w_h))
	{
		if (!guess_wnh(cub, 2))
			return (0);
		free(cub->file.line);
	}
	else if (cub->file.line[0] == 'N' && cub->file.line[1] == 'O'
	&& !cub->file.path[0])
		cub->file.path[0] = take_path(&cub->file.line[3]);
	else if (cub->file.line[0] == 'S' && cub->file.line[1] == 'O'
	&& !cub->file.path[1])
		cub->file.path[1] = take_path(&cub->file.line[3]);
	else if (cub->file.line[0] == 'W' && cub->file.line[1] == 'E'
	&& !cub->file.path[2])
		cub->file.path[2] = take_path(&cub->file.line[3]);
	else if (cub->file.line[0] == 'E' && cub->file.line[1] == 'A'
	&& !cub->file.path[3])
		cub->file.path[3] = take_path(&cub->file.line[3]);
	else if (cub->file.line[0] == 'S' && !cub->file.path[4])
		cub->file.path[4] = take_path(&cub->file.line[3]);
	else if (!floor_ceilur(cub, 2))
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
			if (cub->file.line[0] == '\0')
			free(cub->file.line);
	}
	while (++i < 4)
		if (cub->file.path[i] == NULL)
			return (error("Not every way given", cub));
	if (cub->floor[3] == 0 || cub->ceil[3] == 0)
		return (error("Ceil or floor not given", cub));
	if (!cub->w_w || !cub->w_h)
		return (error("Resolution not given", cub));
	free(cub->file.line);
	return (1);
}
