/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 20:44:09 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/02 21:33:44 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 ** считывание муравьев и проверка что в первой строке число
*/

void	ft_read_ants(char **buf, t_parse *st, t_farm *farm)
{
	int		red;
	char	*tmp;

	red = 0;
	tmp = 0;
	if ((red = get_next_line(0, buf)))
	{
		tmp = *buf;
		while (*tmp)
		{
			if (!ft_isdigit(*tmp))
				error_one();
			tmp++;
		}
		if (!(st->num_ant = ft_atoi(*buf)))
			error_one();
		ft_add_line(farm, buf);
	}
	else
		error_one();
}

/*
 ** малочит два имени из линка и проверяет их на существование
*/

int		ft_work_links(char *buf, t_node *hash_tab[HT_SIZE], \
char **name_f, char **name_s)
{
	char	*tmp;
	char	*end;

	tmp = 0;
	end = 0;
	if (!(tmp = ft_strchr(buf, '-')))
		return (0);
	end = buf;
	while (*end)
		end++;
	if (!(*name_f = ft_strsub(buf, 0, tmp - buf)) || \
	!(*name_s = ft_strsub(buf, tmp - buf + 1, end - tmp)))
		return (0);
	if ((ft_check_name(hash_tab, *name_f) && \
	ft_check_name(hash_tab, *name_s)))
		return (0);
	return (1);
}

/*
 ** проверка строки с линком на валидность
*/

int		ft_check_link(char *buf, t_node *hash_tab[HT_SIZE])
{
	char	*name_first;
	char	*name_sec;

	name_first = NULL;
	name_sec = NULL;
	if (!ft_work_links(buf, hash_tab, \
	&name_first, &name_sec))
		return (0);
	ft_strdel(&name_first);
	ft_strdel(&name_sec);
	return (1);
}

t_link	*ft_new_link(int id_first, int id_sec, int cap)
{
	t_link	*new_link;

	new_link = ft_memalloc(sizeof(t_link));
	if (new_link == NULL)
		return (NULL);
	new_link->flow = 0;
	new_link->parent = id_first;
	new_link->curr = id_sec;
	new_link->cap = cap;
	return (new_link);
}

/*
 ** добавляет линк в соседей
*/

void	ft_add_link(t_farm *farm, int id_first, int id_sec, \
int cap)
{
	t_link *tmp;

	tmp = farm->rooms[id_first]->edges;
	if (!tmp)
		farm->rooms[id_first]->edges = ft_new_link(id_first, id_sec, cap);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_link(id_first, id_sec, cap);
	}
}

/*
 ** парсит линки и проверяет на наличие такого имени
*/

void	ft_parse_link(char *buf, t_farm *farm, t_parse *st)
{
	char	*name_first;
	char	*name_sec;
	int		id_first;
	int		id_sec;

	name_first = NULL;
	name_sec = NULL;
	id_first = 0;
	id_first = 0;
	if (!ft_work_links(buf, st->hash_tab, &name_first, &name_sec))
		error_one();
	id_first = ft_get_elem(name_first, st->hash_tab)->id;
	id_sec = ft_get_elem(name_sec, st->hash_tab)->id;
	ft_strdel(&name_first);
	ft_strdel(&name_sec);
	ft_add_link(farm, id_first, id_sec, 1);
	ft_add_link(farm, id_sec, id_first, 1);
}
