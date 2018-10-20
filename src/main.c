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

static inline void	print_farm(t_data *d)
{
	t_room	*room;
	t_link	*link;

	ft_printf("   \e[1m{BYEL}{TBLC} %d🐜 \n", d->🐜);
	room = d->start;
	while (room)
	{
		ft_printf("{TMAG}%s", room->name);
		link = room->links;
		while (link)
		{
			if (link->room)
				ft_printf("{TCYN}		%s\n", link->room->name);
			link = link->next;
		}
		if (room->next)
			ft_printf("{TYEL}-----------------\n");
		room = room->next;
	}
}

static inline void	ft_error(t_data *d, int n)
{
	if (d->er == -1)
		ft_printf("{TRED}ERROR(init): malloc\n");
	else if (d->er == 1)
		ft_printf("{TRED}ERROR(line[%d]): no line\n", n);
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
		ft_printf("{TRED}ERROR(line[%d]): the specified link exists\n", n);
}

static inline void	init_data(t_data *d, char **line, int *num)
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
	d->start->next = d->end;
	d->output = ft_strnew(1);
	*line = NULL;
	*num = 0;
}

static inline void	read_line(t_data *d, char *line)
{
	if (!d->🐜 && *line != '#' && ft_isnumber(line, ft_strlen(line)))
	{
		if ((d->🐜 = ft_atoi(line)) <= 0)
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
	else if (ft_strchr(line, '-') && d->🐜 && (d->com = 5))
		get_link(d, line, -1);
	else if (d->com != 5)
		d->er = 2;
}

int					main(void)
{
	t_data	d;
	int		ret;
	int		num;
	char	*line;

	init_data(&d, &line, &num);
	while ((ret = get_next_line(0, &line)) > 0 && !d.er)
	{
		d.output = ft_strjoin(d.output, line);
		d.output = ft_strjoin(d.output, "\n");
		read_line(&d, line);
		ft_strdel(&line);
		num++;
	}
	if (ret == -1 || !d.🐜)
		d.er = 1;
	if (d.er)
		ft_error(&d, num);
	else
	{
		ft_printf("%s\n", d.output);
		print_farm(&d);
	}
	ft_strdel(&d.output);
	return (0);
}
