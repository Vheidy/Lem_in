/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:41 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/03 19:28:37 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 ** добавление комнаты в хэш-таблицу
 ** - если по этому индексу уже есть имя, то в след лист
*/

void	ft_add_in_hash_tab(char *name, t_parse *st, int id)
{
	int		index;
	t_node	*tmp;

	index = ft_hasher(name);
	tmp = st->hash_tab[index];
	if (!st->hash_tab[index])
		st->hash_tab[index] = ft_new_list(name, id);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_list(name, id);
	}
	st->count_rooms++;
}

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
 ** общая функция считывания - считывает количество муравьев и элементов и
 ** передает дальше для считывания комнат и связей
*/

int		ft_read(t_parse *st, t_farm *farm)
{
	int		red;
	char	*buf;
	int		fl;

	fl = 0;
	ft_read_ants(&buf, st, farm);
	if (!ft_parse_room(st, fl, &buf, farm))
		error_one();
	ft_parse_link(buf, farm, st);
	while ((red = get_next_line(0, &buf)))
	{
		if (buf[0] != '#')
			ft_parse_link(buf, farm, st);
		ft_add_line(farm, &buf);
	}
	return (0);
}
