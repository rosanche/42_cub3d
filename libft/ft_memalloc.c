/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:24:51 by rosanche          #+#    #+#             */
/*   Updated: 2017/12/08 17:53:10 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*src;
	size_t	i;

	i = 0;
	if (!(src = malloc(size)))
		return (NULL);
	while (i < size)
	{
		src[i] = '\0';
		i++;
	}
	return (src);
}
