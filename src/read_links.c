/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:50:49 by opletsan          #+#    #+#             */
/*   Updated: 2018/10/17 16:50:52 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	write_link2(t_data *d, t_room *r1, t_room *r2)
{
	t_link	*link;

	link = r2->links;
	while (link->next)
		link = link->next;
	if (!(link->next = (t_link*)ft_memalloc(sizeof(t_link))))
	{
		d->er = -1;
		return ;
	}
	link->next->room = r1;
}

static inline void	write_link1(t_data *d, t_room *r1, t_room *r2)
{
	t_link	*link;

	if (!r1 || !r2)
	{
		d->er = 9;
		return ;
	}
	link = r1->links;
	while (link->next)
	{
		if (link->room == r2)
		{
			d->er = 10;
			return ;
		}
		link = link->next;
	}
	if (!(link->next = (t_link*)ft_memalloc(sizeof(t_link))))
	{
		d->er = -1;
		return ;
	}
	link->next->room = r2;
	write_link2(d, r1, r2);
}

void				get_link(t_data *d, char *line, int i)
{
	char	*sname;
	char	*fname;

	if (!d->start->name || !d->end->name)
	{
		d->er = 7;
		return ;
	}
	sname = NULL;
	fname = NULL;
	while (line[++i])
	{
		if (line[i] == '-' && !sname)
		{
			fname = ft_strsub(line, 0, i);
			sname = ft_strsub(&line[i + 1], 0, ft_strlen(&line[i + 1]));
		}
		else if ((line[i] == '-' && sname) || (line[i] >= 9 && line[i] <= 13)
				|| line[i] == ' ' || (sname && !ft_strcmp(sname, fname)))
		{
			d->er = 8;
			return ;
		}
	}
	write_link1(d, src_room(d, fname), src_room(d, sname));
}
