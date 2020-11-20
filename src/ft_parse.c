/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asybil <asybil@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:41 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/21 02:35:45 by asybil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 ** создает комнату (1 малок)
*/

room	*ft_create_room(int id, char *name)
{
	room	*new_room;

	new_room = ft_memalloc(sizeof(room));
	new_room->id = id;
	new_room->level = -1;
	new_room->name = name;
	return (new_room);
}

/*
 ** заполняет новую структуру комнатами из хэш-таблицы
*/

void	ft_farm_set_room(room **rooms, int count, t_lem *st)
{
	int	i;
	int count_room;
	t_node *tmp;

	i = -1;
	count_room = 0;
	tmp = NULL;
	while (count_room < count && ++i < HT_SIZE)
		if (st->hash_tab[i])
		{
			tmp = st->hash_tab[i];
			rooms[tmp->id] = ft_create_room(tmp->id, tmp->name);
			count_room++;
			while (tmp->next)
			{
				tmp = tmp->next;
				rooms[tmp->id] = ft_create_room(tmp->id, tmp->name);
				count_room++;
			}
		}
}

/*
 ** возвращает указатель на лист с переданным именем
*/

t_node	*ft_get_elem(char *name, t_node *hash_tab[HT_SIZE])
{
	int		index;
	t_node	*tmp;

	index = ft_hasher(name);
	tmp = hash_tab[index];
	while (tmp->next && ft_strcmp(tmp->name, name))
		tmp = tmp->next;
	if (!tmp->next && ft_strcmp(tmp->name, name))
		error();
	return (tmp);
}

/*
 ** инициализация структуры 
*/

int		ft_init_farm(farm *farm, t_lem *st)
{
	if (!st->start || !st->end)
		error();
	farm->id_start = ft_get_elem(st->start, st->hash_tab)->id;
	farm->id_end = ft_get_elem(st->end, st->hash_tab)->id;
	// printf("id_end: %d\n", farm->id_end);
	farm->count_rooms = st->count_rooms;
	farm->count_ants = st->num_ant;
	if (!(farm->rooms = ft_memalloc(sizeof(room*) * st->count_rooms + 1)))
		error();
	ft_farm_set_room(farm->rooms, farm->count_rooms, st);
	return (1);
}

/*
 ** общая функция считывания - считывает количество муравьев и элементов и 
 ** передает дальше для считывания комнат и связей
*/

int		ft_read(t_lem *st, farm	*farm)
{
	int		red;
	char	*buf;
	int		fl;

	fl = 0;
	ft_read_ants(&buf, st);
	if (!ft_parse_room(st, fl, &buf, farm))
			error();
	ft_parse_link(buf, farm, st);
	ft_strdel(&buf);
	while ((red = get_next_line(0, &buf)))
	{
		if(buf[0] != '#')
			ft_parse_link(buf, farm, st);
		ft_strdel(&buf);
	}
	return (0);
}