/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 18:38:39 by rosanche          #+#    #+#             */
/*   Updated: 2017/12/04 03:22:59 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, unsigned char c)
{
	while (*s != c && *s)
		s++;
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}
