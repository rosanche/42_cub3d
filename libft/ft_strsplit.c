/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:09:10 by rosanche          #+#    #+#             */
/*   Updated: 2017/12/20 11:31:28 by rosanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		count_word(char const *s, int c)
{
	int i;
	int word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			word++;
		while (s[i] != c && s[i])
			i++;
	}
	return (word);
}

static	char	*word_fill(char const *s, int pos, int c)
{
	int		i;
	char	*src;

	i = pos;
	while (s[i] != c && s[i])
		i++;
	if (!(src = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[pos] != c && s[pos])
	{
		src[i] = s[pos];
		i++;
		pos++;
	}
	src[i] = '\0';
	return (src);
}

char			**ft_strsplit(char const *s, int c)
{
	int		i;
	int		n;
	int		word;
	char	**tab;

	i = 0;
	if (!s)
		return (NULL);
	word = count_word(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (word + 1))))
		return (NULL);
	n = 0;
	while (i < word)
	{
		while (s[n] == c)
			n++;
		tab[i] = word_fill(s, n, c);
		i++;
		while (s[n] != c && s[n] != '\0')
			n++;
	}
	tab[i] = 0;
	return (tab);
}
