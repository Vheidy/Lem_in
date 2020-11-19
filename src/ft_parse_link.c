/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 20:44:09 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/19 15:46:13 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 ** считывание муравьев и проверка что в первой строке число
*/
void	ft_read_ants(char **buf, t_lem *st)
{
	int red;
	char *tmp;

	if ((red = get_next_line(0, buf)))
	{
		tmp = *buf;
		while (*tmp)
		{
			if (!ft_isdigit(*tmp))
				error();
			tmp++;
		}
		
		if (!(st->num_ant = ft_atoi(*buf)))
			error();
		free(*buf);
	}
	else
		error();
}

/*
 ** малочит два имени из линка и проверяет их на существование
*/
int		ft_work_links(char *buf, t_node *hash_tab[HT_SIZE], \
char **name_f, char **name_s)
{
	char	*tmp;
	char	*end;

	if (!(tmp = ft_strchr(buf, '-')))
		return (0);
	end = buf;
	while (*end)
		end++;
	if (!(*name_f = ft_strsub(buf, 0, tmp - buf)) || \
	!(*name_s = ft_strsub(buf, tmp - buf + 1, end - tmp))) // malloc * 2
		return (0);
	if ((ft_check_name(hash_tab, *name_f) && \
	ft_check_name(hash_tab,*name_s)))
		return (0);
	return (1);
}

/*
 ** проверка строки с линком на валидность
*/
int		ft_check_link(char *buf, t_node *hash_tab[HT_SIZE])
{
	char	*name_f;
	char	*name_s;

	name_f = NULL;
	name_s = NULL;
	if (!ft_work_links(buf, hash_tab, \
	&name_f, &name_s))
		return (0);
	free(name_s);
	free(name_f);
	return (1);
}

t_link	*ft_new_link(int id_f, int id_s, int cap)
{
	t_link	*new_link;

	new_link = malloc(sizeof(t_link));
	new_link->next = NULL;
	new_link->parent = id_f;
	new_link->curr = id_s;
	new_link->flow = 0;
	new_link->cap = cap;
	return (new_link);
}

/*
 ** добавляет линк в соседей
*/
void	ft_add_link(farm *farm, int id_f, int id_s, \
int cap)
{
	t_link *tmp;

	tmp = farm->rooms[id_f]->edges;
	if (!tmp)
		farm->rooms[id_f]->edges = ft_new_link(id_f, id_s, cap);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_link(id_f, id_s, cap);
	}
}

/*
 ** парсит линки и проверяет на наличие такого имени
*/
void	ft_parse_link(char *buf, farm *farm, t_lem *st)
{
	char	*name_f;
	char	*name_s;
	int		id_f;
	int		id_s;

	name_f = NULL;
	name_s = NULL;
	if (!ft_work_links(buf, st->hash_tab, &name_f, &name_s)) // malloc * 2
		error();
	id_f = ft_get_elem(name_f, st->hash_tab)->id;
	id_s = ft_get_elem(name_s, st->hash_tab)->id;
	ft_add_link(farm, id_f, id_s, 1);
	ft_add_link(farm, id_s, id_f, 1);
}
