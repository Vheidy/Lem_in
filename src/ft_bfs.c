/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asybil <asybil@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:08:57 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/21 02:20:29 by asybil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 ** получить первый элемент и удалить его из очереди
*/
int		ft_get_first(t_node **deque)
{
	t_node	*tmp;
	int		id;

	id = 0;
	tmp = 0;
	tmp = *deque;
	id = (*deque)->id;
	*deque = (*deque)->next;
	ft_memdel((void**)&tmp);
	return (id);
}

/*
 ** добавить элемент в конец очереди
*/
void	ft_add_deque(t_node **deque, int id)
{
	t_node	*tmp;

	tmp = 0;
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

	tmp = 0;
	curr_id = 0;
	while (deque)
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

/*
**	Unused function 
*/
/*static void	ft_form_route(t_route *route, int id, farm *farm)
{
	
}*/

/*
 ** проверка на наличие пути от старта к финишу
*/
void	ft_algo(farm *farm)
{
	int		id;
	t_node	*deque;
	// t_route	*best; commented as unused parameter
	// t_route	*add; commented because not used
	
	deque = NULL;
	id = 0;
	// best = 0;
	// add = 0;
	ft_add_deque(&deque, farm->id_start);
	farm->rooms[farm->id_start]->level = 0;
	while ((id = ft_bfs(farm->rooms, &deque, farm->id_end)) != -1)
	{
		// ft_form_route(best, id, farm); commented because body of called function is empty
		// ft_dfs(farm); commented because function not found
	}
	if((id = ft_bfs(farm->rooms, &deque, farm->id_end)) == -1)
		error();
	
}