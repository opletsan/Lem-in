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
	struct s_link	*prev;
}				t_link;

typedef struct	s_room
{
	char			*name;
	int				dis;
	int				ant;
	t_link			*links;
	struct s_room	*next;
}				t_room;

typedef struct	s_data
{
	char		flg[120];
	char		*output;
	int			🐜;
	int			com;
	int			er;
	t_room		*start;
	t_room		*end;
	t_link		*way_st;
	t_link		*way_end;
}				t_data;

t_room			*src_room(t_data *d, char *name);
void			get_room(t_data *d, char *line);
void			get_link(t_data *d, char *line, char *sname, char *fname);
void			src_way(t_data *d, t_link *q, t_link *cur, t_link *end);
void			ft_print_way(t_data *d);
void			ft_print_farm(t_data *d);
void			ft_error(t_data *d, int n);
void			color_ant(int ant, char *name);
void			read_flag(t_data *d, char *av);

#endif
