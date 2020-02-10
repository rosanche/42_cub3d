/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:32:10 by rosanche          #+#    #+#             */
/*   Updated: 2017/12/08 17:52:00 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t dest_len;
	size_t src_len;
	size_t total_size;

	dest_len = 0;
	total_size = ft_strlen(src);
	while (dest[dest_len] != '\0' && dest_len < size)
	{
		dest_len++;
		if (size == dest_len)
			return (total_size + size);
	}
	dest_len = ft_strlen(dest);
	src_len = 0;
	total_size += (size <= dest_len ? size : dest_len);
	while (src[src_len] != '\0' && dest_len + 1 < size)
	{
		dest[dest_len] = src[src_len];
		dest_len++;
		src_len++;
	}
	dest[dest_len] = '\0';
	return (total_size);
}
