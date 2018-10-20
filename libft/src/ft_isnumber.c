/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 20:15:30 by opletsan          #+#    #+#             */
/*   Updated: 2018/10/15 20:16:34 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isnumber(const char *str, size_t len)
{
	size_t	i;

	i = 0;
	if (!len || !str || !*str)
		return (0);
	while (str[i] && i < len)
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}
