/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:49:21 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/03 20:02:00 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 ** инициализация маршрута - проставляет старт и енд и малочит под вершины
*/

t_route	*ft_init_route(int size, int id_first, int id_last, int fl)
{
	t_route	*tmp;

	tmp = malloc(sizeof(t_route));
	(tmp)->next = NULL;
	(tmp)->size = size;
	(tmp)->tops = malloc(sizeof(int) * (tmp)->size);
	(tmp)->tops[0] = id_first;
	if (!fl)
		(tmp)->tops[tmp->size - 1] = id_last;
	else
		(tmp)->tops[1] = id_last;
	(tmp)->count_ants = 0;
	return (tmp);
}

/*
 ** создает комнату (1 малок)
*/

t_room	*ft_create_room(int id, char *name)
{
	t_room	*new_room;

	new_room = ft_memalloc(sizeof(t_room));
	new_room->id = id;
	new_room->level = -1;
	new_room->visited = 0;
	new_room->in = -1;
	new_room->out = -1;
	new_room->name = ft_strdup(name);
	return (new_room);
}

/*
 ** заполняет новую структуру комнатами из хэш-таблицы
*/

void	ft_farm_set_room(t_room **rooms, int count, t_parse *st)
{
	int		i;
	int		count_room;
	t_node	*tmp;

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
		error_one();
	return (tmp);
}

/*
 ** инициализация структуры
*/

int		ft_init_farm(t_farm *farm, t_parse *st)
{
	if (!st->start || !st->end)
		error_one();
	farm->id_start = ft_get_elem(st->start, st->hash_tab)->id;
	farm->id_end = ft_get_elem(st->end, st->hash_tab)->id;
	farm->count_rooms = st->count_rooms;
	farm->count_ants = st->num_ant;
	if (!(farm->rooms = malloc(sizeof(t_room *) * st->count_rooms)))
		error_one();
	ft_farm_set_room(farm->rooms, farm->count_rooms, st);
	return (1);
}
