/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 20:49:44 by opletsan          #+#    #+#             */
/*   Updated: 2017/11/06 21:12:46 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int x)
{
	int i;

	i = 1;
	if (x <= 0)
		return (0);
	while ((i * i) != x)
	{
		if ((i * i) > x)
			return (0);
		i++;
	}
	return (i);
}
