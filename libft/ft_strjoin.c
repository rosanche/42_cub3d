/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 19:00:10 by rosanche          #+#    #+#             */
/*   Updated: 2017/12/08 17:17:35 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		v;
	char	*src;

	if (!s1 || !s2)
		return (NULL);
	if (!(src = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) +
						1))))
		return (NULL);
	i = 0;
	v = -1;
	while (s1[++v] && s1 + i != s2)
		src[i++] = s1[v];
	v = -1;
	while (s2[++v])
		src[i++] = s2[v];
	src[i] = '\0';
	return (src);
}
