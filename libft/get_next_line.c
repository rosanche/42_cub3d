/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 10:43:39 by rosanche          #+#    #+#             */
/*   Updated: 2019/12/18 15:34:37 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		found_eol(char *tmp, char *rpl, char **line, char *str)
{
	int i;
	int v;

	i = 0;
	v = -1;
	while (tmp[i] != EOL && tmp[i] != EOL)
		i++;
	while (++v < i)
		str[v] = tmp[v];
	rpl = *line;
	*line = ft_strjoin(rpl, str);
	free(rpl);
	i++;
	ft_memmove(tmp, tmp + i, ft_strlen(tmp) - i);
	ft_memset(tmp + ft_strlen(tmp) - i, '\0', i);
	free(str);
	return (1);
}

int		eol_search(char **line, char **tmp, char *str)
{
	char	*rpl;
	int		i;

	rpl = NULL;
	i = 0;
	if (ft_strchr(*tmp, EOL))
		return (found_eol(*tmp, rpl, line, str));
	else if (*tmp)
	{
		i = ft_strlen(*tmp);
		rpl = *line;
		*line = ft_strjoin(rpl, *tmp);
		free(rpl);
		ft_memset(*tmp, '\0', BUFFER_SIZE);
	}
	return (0);
}

int		return_result(char **line, char **tmp, char *str, const int fd)
{
	int	res;

	while ((res = read(fd, (void *)*tmp, BUFFER_SIZE)) > 0)
	{
		if (eol_search(line, tmp, str))
			return (1);
	}
	free(*tmp);
	*tmp = NULL;
	free(str);
	if ((!line && res <= 0) || res < 0)
		return (-1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char *tmp = NULL;
	char		*str;

	if (fd < 0 || !(line) || BUFFER_SIZE <= 0)
		return (-1);
	if (!(str = ft_strnew(BUFFER_SIZE)))
		return (-1);
	*line = ft_strnew(0);
	if (tmp)
	{
		if (eol_search(line, &tmp, str))
			return (1);
	}
	if (!(tmp) && !(tmp = ft_strnew(BUFFER_SIZE)))
		return (-1);
	return (return_result(line, &tmp, str, fd));
}
