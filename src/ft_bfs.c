/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:08:57 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/17 12:54:52 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
int		ft_bfs(room **rooms, int id_start, int id_end)
{
	t_node	*deque;
	t_node	*tmp;
	int		curr_id;

	deque = ft_new_list(NULL, id_start);
	rooms[id_start]->level = 0;
	while (deque)
	{
		curr_id = ft_get_first(&deque);
		tmp = rooms[curr_id]->neighbors;
		while (tmp)
		{
			if (tmp->id == id_end)
				return (curr_id);
			if (rooms[tmp->id]->level == -1)
			{
				rooms[tmp->id]->level = rooms[curr_id]->level + 1;
				ft_add_deque(&deque, tmp->id);
			}
			tmp = tmp->next;
		}
	}
	return (-1);
}

/*
 ** проверка на наличие пути от старта к финишу
*/
void	ft_algo(farm *farm)
{
	int		id;

	if((id = ft_bfs(farm->rooms, farm->id_start, \
	farm->id_end)) == -1)
		error();
	
}