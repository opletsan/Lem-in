/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:48:55 by opletsan          #+#    #+#             */
/*   Updated: 2018/10/25 16:48:57 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	color_ant(int ant, char *name)
{
	int col;

	col = ant % 7;
	if (!col)
		ft_printf("L%d-%s ", ant, name);
	else if (col == 1)
		ft_printf("{TGRN}L%d-%s ", ant, name);
	else if (col == 2)
		ft_printf("{TBLU}L%d-%s ", ant, name);
	else if (col == 3)
		ft_printf("{TYEL}L%d-%s ", ant, name);
	else if (col == 4)
		ft_printf("{TMAG}L%d-%s ", ant, name);
	else if (col == 5)
		ft_printf("{TCYN}L%d-%s ", ant, name);
	else if (col == 6)
		ft_printf("{TRED}L%d-%s ", ant, name);
}

void	ft_print_way(t_data *d)
{
	t_link *way;

	way = d->way_st;
	ft_printf("\n{TYEL}WAY: ");
	while (way && way->room)
	{
		ft_printf("{TYEL}%s", way->room->name);
		if ((way = way->next))
			ft_printf("{TYEL} ➢ ");
	}
	write(1, "\n", 1);
}

void	ft_print_farm(t_data *d)
{
	t_room *room;
	t_link *link;

	ft_printf("\n		\e[1m{BYEL}{TBLC} %d🐜 \n", d->🐜);
	ft_printf("{TMAG}ROOM		{TBLU}DISTANCE		{TCYN}LINK\n");
	room = d->start;
	while (room && room->dis)
	{
		ft_printf("{TMAG}%.6s", room->name);
		if (ft_strlen(room->name) > 6)
			ft_printf("{TMAG}.");
		ft_printf("		{TBLU}%d", room->dis);
		link = room->links->next;
		while (link)
		{
			if (room->links->next == link)
				ft_printf("{TCYN}			%s\n", link->room->name);
			else
				ft_printf("{TCYN}					%s\n", link->room->name);
			link = link->next;
		}
		if ((room = room->next) && room->links->next)
			ft_printf("{TYEL}----------------------------------------------\n");
	}
}

void	ft_error(t_data *d, int n)
{
	if (d->er == -1)
		ft_printf("{TRED}ERROR(init): malloc\n");
	else if (d->er == 1)
		ft_printf("{TRED}ERROR(line[%d]): no ants or error gnl\n", n);
	else if (d->er == 2)
		ft_printf("{TRED}ERROR(line[%d]): nonvalid line or map structure\n", n);
	else if (d->er == 3)
		ft_printf("{TRED}ERROR(line[%d]): nonvalid number ants\n", n);
	else if (d->er == 4)
		ft_printf("{TRED}ERROR(line[%d]): nonvalid room\n", n);
	else if (d->er == 5)
		ft_printf("{TRED}ERROR(line[%d]): the specified room exists\n", n);
	else if (d->er == 6)
		ft_printf("{TRED}ERROR(line[%d]): the specified command exists\n", n);
	else if (d->er == 7)
		ft_printf("{TRED}ERROR: no command 'start' or/and 'end'\n");
	else if (d->er == 8)
		ft_printf("{TRED}ERROR(line[%d]): nonvalid link\n", n);
	else if (d->er == 9)
		ft_printf("{TRED}ERROR(line[%d]): a nonexistent link to the room\n", n);
	else if (d->er == 10)
		ft_printf("{TRED}ERROR: no way\n");
	else
		ft_printf("{TRED}ERROR: nonvalid map structure\n");
}

void	read_flag(t_data *d, char *av)
{
	size_t i;

	i = 0;
	if (av[0] != '-')
		return ;
	if (!av[1])
	{
		ft_strcpy(d->flg, "\nError: Invalid argument.\nusage: lem-in [-flw]\n"
							"f - show farm\nl - show leaks\n"
							"w - show all possible ways on output\n");
		return ;
	}
	while (*(++av))
	{
		if (*av == 'f' || *av == 'l' || *av == 'w')
			d->flg[i++] = *av;
		else
			ft_strcpy(d->flg, "\nError: Invalid argument.\n"
						"usage: lem-in [-flw]\nf - show farm\nl - show leaks\n"
						"w - show all possible ways on output\n");
	}
}
