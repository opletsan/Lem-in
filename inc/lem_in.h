/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opletsan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 13:12:02 by opletsan          #+#    #+#             */
/*   Updated: 2018/10/14 13:21:13 by opletsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include "libft.h"
# include <stdio.h>

typedef struct	s_link
{
	struct s_room	*room;
	struct s_link	*next;
}				t_link;

typedef struct	s_room
{
	char			*name;
	t_link			*links;
	struct s_room	*next;
}				t_room;

typedef struct	s_data
{
	char		*output;
	int			🐜;
	int			com;
	int			er;
	t_room		*start;
	t_room		*end;
}				t_data;

t_room			*src_room(t_data *d, char *name);
void			get_room(t_data *d, char *line);
void			get_link(t_data *d, char *line, int i);

#endif
