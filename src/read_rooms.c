/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 22:22:06 by opletsan          #+#    #+#             */
/*   Updated: 2018/10/14 22:22:08 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room					*src_room(t_data *d, char *name)
{
	t_room	*room;

	if (!name)
		return (NULL);
	room = d->start;
	while (room)
	{
		if (room->name && !(ft_strcmp(room->name, name)))
			return (room);
		room = room->next;
	}
	return (NULL);
}

static inline void		write_room(t_data *d, char *name)
{
	t_room	*room;

	room = d->end;
	while (room->next)
		room = room->next;
	if (!(room->next = (t_room*)ft_memalloc(sizeof(t_room))))
	{
		d->er = -1;
		return ;
	}
	room = room->next;
	room->name = name;
	if (!(room->links = (t_link*)ft_memalloc(sizeof(t_link))))
		d->er = -1;
}

static inline char		*valid_roomname(char *line)
{
	char	*name;
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = -1;
	if (*line != 'L' && (tmp1 = ft_strchr(line, ' ')))
	{
		if (!(name = ft_strsub(line, 0, tmp1 - line)))
			return (NULL);
		++tmp1;
		while (name[++i])
			if (name[i] == '-' || (name[i] >= 9 && name[i] <= 13))
			{
				free(name);
				return (NULL);
			}
		if ((tmp2 = ft_strchr(tmp1, ' ')) && ft_isnumber(tmp1, tmp2 - tmp1)
																	&& ++tmp2)
			if (ft_isnumber(tmp2, ft_strlen(tmp2)))
				return (name);
		free(name);
	}
	return (NULL);
}

void					get_room(t_data *d, char *line)
{
	char	*name;

	if ((name = valid_roomname(line)))
	{
		if (d->com == 1)
		{
			d->start->name = name;
			d->com = 2;
		}
		else if (d->com == 3)
		{
			d->end->name = name;
			d->com = 4;
		}
		else if (!src_room(d, name))
			write_room(d, name);
		else
			d->er = 5;
	}
	else
		d->er = 4;
}
