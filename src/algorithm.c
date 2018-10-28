/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 22:14:19 by opletsan          #+#    #+#             */
/*   Updated: 2018/10/20 22:14:48 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void		free_queue(t_link *q)
{
	t_link	*tmp;

	while (q)
	{
		tmp = q;
		q = q->next;
		free(tmp);
	}
}

static inline t_link	*add_q(t_link *cur, t_link *end)
{
	t_link	*l;

	l = cur->room->links;
	while (l)
	{
		if (l->room && !l->room->dis)
		{
			l->room->dis = cur->room->dis + 1;
			if (!(end->next = (t_link*)ft_memalloc(sizeof(t_link))))
				return (NULL);
			end = end->next;
			end->room = l->room;
		}
		l = l->next;
	}
	return (end);
}

static inline void		backtrack(t_data *d)
{
	t_link	*l;
	t_link	*tmp;

	d->way_st->room = d->end;
	while (d->way_st->room->dis != 1)
	{
		tmp = d->way_st;
		l = d->way_st->room->links->next;
		while (l && l->room->dis != d->way_st->room->dis - 1)
			l = l->next;
		if (!(d->way_st->prev = (t_link*)ft_memalloc(sizeof(t_link))))
		{
			d->er = -1;
			return ;
		}
		d->way_st = d->way_st->prev;
		d->way_st->room = l->room;
		d->way_st->next = tmp;
	}
}

void					src_way(t_data *d, t_link *q, t_link *cur, t_link *end)
{
	if (!(q = (t_link*)ft_memalloc(sizeof(t_link))))
	{
		d->er = -1;
		return ;
	}
	q->room = d->start;
	q->room->dis = 1;
	cur = q;
	end = q;
	while (cur && cur->room != d->end)
	{
		if (!(end = add_q(cur, end)))
		{
			free_queue(q);
			d->er = -1;
			return ;
		}
		cur = cur->next;
	}
	free_queue(q);
	if (!d->end->dis && !d->er)
		d->er = 10;
	else if (d->end->dis)
		backtrack(d);
}
