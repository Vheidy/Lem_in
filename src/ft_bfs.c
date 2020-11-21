/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:08:57 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/19 17:14:18 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 ** написать функцию блокирующих потоков
 ** И ту которая будет складывать блок поток и текущий и смотреть разрушились ли ребра
    добавить алгоритм движения по количеству муравьев
*/

/*
 ** получить первый элемент и удалить его из очереди
*/
int		ft_get_first(t_node **deque)
{
	t_node	*tmp;
	int		id;

	tmp = *deque;
	id = (*deque)->id;
	*deque = (*deque)->next;
	// ft_del_list(tmp);
	free(tmp);
	return (id);
}

/*
 ** добавить элемент в конец очереди
*/
void	ft_add_deque(t_node **deque, int id)
{
	t_node	*tmp;

	if (!*deque)
	{
		*deque = ft_new_list(NULL, id);
	}
	else
	{
		tmp = *deque;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_list(NULL, id);
	}
}

/*
 ** обход в ширину,
 ** если путь к концу найден вернет id комнаты от которой к нему можно дойти
 ** если нет то -1
*/
int		ft_bfs(room **rooms, t_node **deque, int id_end)
{
	t_link	*tmp;
	int		curr_id;

	while (*deque)
	{
		curr_id = ft_get_first(deque);
		tmp = rooms[curr_id]->edges;
		while (tmp)
		{
			if (tmp->curr == id_end)
				return (curr_id);
			if (rooms[tmp->curr]->level == -1)
			{
				rooms[tmp->curr]->level = rooms[curr_id]->level + 1;
				ft_add_deque(deque, tmp->curr);
			}
			tmp = tmp->next;
		}
	}
	return (-1);
}

void	ft_form_route(t_route **route, int id, farm *farm)
{
	int		i;
	room	*tmp_room;
	t_link	*tmp_link;

	i = farm->rooms[id]->level + 1;
	tmp_room = farm->rooms[id];
	(*route) = malloc(sizeof(t_route));
	(*route)->size = tmp_room->level + 2;
	(*route)->tops = malloc(sizeof(int) * (*route)->size);
	(*route)->tops[0] = farm->id_start;
	(*route)->tops[tmp_room->level + 1] = farm->id_end;
	while (--i > 0)
	{
		(*route)->tops[i] = id;
		tmp_link = tmp_room->edges;
		while (farm->rooms[tmp_link->curr]->level != tmp_room->level - 1)
			tmp_link = tmp_link->next;
		id = farm->rooms[tmp_link->curr]->id;
		tmp_room = farm->rooms[id];
	}
}

/*
 ** проверка на наличие пути от старта к финишу
*/
void	ft_algo(farm *farm)
{
	int		id;
	t_node	*deque;
	t_route	*best;
	// t_route	*add;

	deque = ft_new_list(NULL, farm->id_start);
	best = NULL;
	farm->rooms[farm->id_start]->level = 0;
	if ((id = ft_bfs(farm->rooms, &deque, farm->id_end)) == -1)
		error();
	ft_form_route(&best, id, farm);
}