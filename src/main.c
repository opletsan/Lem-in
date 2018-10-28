/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 13:07:47 by opletsan          #+#    #+#             */
/*   Updated: 2018/10/14 13:07:58 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	print_way(t_data *d, t_link *way)
{
	while (d->end->ant != d->🐜)
	{
		while (way->prev && way->room->ant != d->🐜)
		{
			if (way->room->ant && way->next)
				color_ant(++way->next->room->ant, way->next->room->name);
			way = way->prev;
		}
		if (way->next->room->ant < d->🐜)
			color_ant(++way->next->room->ant, way->next->room->name);
		way = d->way_end;
		ft_printf("\n");
	}
}

static inline void	read_line(t_data *d, char *line)
{
	if (!d->🐜 && *line != '#' && ft_isnumber(line, ft_strlen(line)))
	{
		if (ft_strlen(line) > 10 || (d->🐜 = ft_atoi(line)) <= 0)
			d->er = 3;
	}
	else if (!ft_strcmp(line, "##start") && d->🐜 && !d->start->name &&
			d->com != 3 && d->com != 1)
		d->com = 1;
	else if (!ft_strcmp(line, "##end") && d->🐜 && !d->end->name &&
			d->com != 3 && d->com != 1)
		d->com = 3;
	else if ((!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end")) &&
			d->🐜)
		d->er = 6;
	else if (*line == '#' && ft_strcmp(line, "##start") &&
			ft_strcmp(line, "##end"))
		return ;
	else if (ft_strchr(line, ' ') && d->🐜 && d->com != 5)
		get_room(d, line);
	else if (ft_strchr(line, '-') && d->🐜)
		get_link(d, line, NULL, NULL);
	else if (d->com != 5)
		d->er = 2;
	else
		d->er = 8;
}

static inline void	init_data(t_data *d)
{
	ft_bzero(d, sizeof(t_data));
	if (!(d->start = (t_room*)ft_memalloc(sizeof(t_room))) ||
		!(d->start->links = (t_link*)ft_memalloc(sizeof(t_link))))
	{
		d->er = -1;
		return ;
	}
	if (!(d->end = (t_room*)ft_memalloc(sizeof(t_room))) ||
		!(d->end->links = (t_link*)ft_memalloc(sizeof(t_link))))
	{
		d->er = -1;
		return ;
	}
	if (!(d->way_st = (t_link*)ft_memalloc(sizeof(t_link))))
	{
		d->er = -1;
		return ;
	}
	d->way_end = d->way_st;
	d->start->next = d->end;
	d->output = ft_strnew(1);
}

static inline int	read_data(t_data *d, char *line, int n)
{
	int		ret;
	char	*str;

	while (!d->er && (ret = get_next_line(0, &line)) > 0)
	{
		read_line(d, line);
		if (!d->er)
		{
			str = d->output;
			d->output = ft_strjoin(str, line);
			free(str);
			str = d->output;
			d->output = ft_strjoin(str, "\n");
			free(str);
		}
		if (d->er == -2)
			d->er = 0;
		ft_strdel(&line);
		++n;
	}
	if (!d->er && (ret == -1 || !d->🐜))
		d->er = 1;
	return (n);
}

int					main(int ac, char **av)
{
	t_data	d;
	int		n;

	init_data(&d);
	if (ac > 1)
		read_flag(&d, av[1]);
	n = read_data(&d, NULL, 0);
	if (d.com == 5)
		src_way(&d, NULL, NULL, NULL);
	if ((d.er && !d.end->dis) || !d.end->dis)
		ft_error(&d, n);
	else
	{
		ft_printf("%s\n", d.output);
		print_way(&d, d.way_end);
		if (d.flg[0] == '\n')
			ft_printf("%s", d.flg);
		if (d.flg[0] != '\n' && ft_strchr(d.flg, 'w'))
			ft_print_way(&d);
		if (d.flg[0] != '\n' && ft_strchr(d.flg, 'f'))
			ft_print_farm(&d);
	}
	if (d.flg[0] != '\n' && ft_strchr(d.flg, 'l'))
		system("echo && leaks -q lem-in");
	return (0);
}
