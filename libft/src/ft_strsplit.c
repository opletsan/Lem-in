/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:44:06 by opletsan          #+#    #+#             */
/*   Updated: 2017/11/09 21:34:58 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numline(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static size_t	ft_numlett(char const *s, unsigned int i, char c)
{
	size_t	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		i++;
		len++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	char	**rres;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	res = (char**)malloc(sizeof(char*) * ft_numline(s, c) + 1);
	if (!res)
		return (NULL);
	rres = res;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			*res = ft_strsub(s, i, ft_numlett(s, i, c));
			i += ft_numlett(s, i, c);
			res++;
		}
	}
	*res = NULL;
	return (rres);
}
