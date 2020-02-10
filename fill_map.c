/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:44:01 by rosanche          #+#    #+#             */
/*   Updated: 2020/02/07 15:44:44 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		height_n_fill(int fd, t_cub *cub, char *line)
{
	int count;
	int ret;

	count = 1;
	ret = -1;
	cub->tab->sm[0] = ft_strdup(line);
	while ((ret = get_next_line(fd, &line)) >= 0 && line)
	{
		cub->tab->sm[count] = ft_strdup(line);
		count++;
		if (ret == 0)
			break ;
	}
	cub->tab->map_height = count;
	free(line);
	line = NULL;
	return (1);
}

int		ft_strlen_tab(char **str)
{
	int i;

	i = 0;
	while (str[i][0] == '1' && str[i][ft_strlen(str[i]) - 1] == '1')
		i++;
	return (i);
}

int		width(t_gril *grill, t_cub *cub)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (count < cub->tab->map_height)
	{
		i = 0;
		while (grill->sm[count][i])
		{
			if (grill->sm[count][i] == ' ')
			{
				ft_memmove(grill->sm[count] + i, grill->sm[count]
				+ i + 1, ft_strlen(grill->sm[count]) - i);
				ft_memset(grill->sm[count] +
				ft_strlen(grill->sm[count]), '\0', 1);
			}
			if (grill->sm[count][i] == '2')
				cub->nb_sprite++;
			i++;
		}
		count++;
	}
	grill->map_width = ft_strlen(grill->sm[0]);
	return (1);
}
