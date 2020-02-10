/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:32:22 by rosanche          #+#    #+#             */
/*   Updated: 2017/12/08 17:52:47 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*u_dest;
	unsigned char	*u_src;

	u_src = (unsigned char *)src;
	u_dest = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		u_dest[i] = u_src[i];
		if (u_dest[i] == (unsigned char)c)
			return (&(u_dest[i + 1]));
		i++;
	}
	return (NULL);
}
