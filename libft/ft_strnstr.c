/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 18:40:55 by rosanche          #+#    #+#             */
/*   Updated: 2017/12/20 08:17:37 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *foin, const char *aiguille, size_t len)
{
	size_t		i;
	size_t		n;
	const char	*ptr;

	i = 0;
	if (!aiguille[0])
		return ((char *)foin);
	while (foin[i] && i < len)
	{
		n = 0;
		if (aiguille[n] == foin[i])
		{
			ptr = &(foin[i]);
			while (aiguille[n] && aiguille[n] == foin[i + n] && i + n < len)
				n++;
			if (!(aiguille[n]))
				return ((char *)ptr);
		}
		i++;
	}
	return (NULL);
}
