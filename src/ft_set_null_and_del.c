/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_null_and_del.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:19:27 by polina            #+#    #+#             */
/*   Updated: 2020/11/29 20:15:53 by polina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 ** удалить очередь
*/
void	ft_del_deque(t_node **deque)
{
	t_node	*tmp;
	t_node	*next;

	tmp = *deque;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*deque = NULL;
}

/*
 ** удаление пути
*/
void	ft_del_route(t_route **route)
{
	t_route	*tmp;
	t_route	*next;

	tmp = *route;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*route = NULL;
}

/*
 ** обнуление слоев
*/
void	ft_set_null_level(farm *farm, room ***rooms)
{
	t_node	*deque;
	t_link	*edges;
	int		id;

	deque = ft_new_list(NULL, farm->rooms[farm->id_start]->out);
	while (deque)
	{
		id = ft_get_first(&deque);
		(*rooms)[id]->level = -1;
		edges = (*rooms)[id]->edges;
		while (edges)
		{
			if ((*rooms)[edges->curr]->level != -1)
			{
				(*rooms)[edges->curr]->level = -1;
				ft_add_deque(&deque, edges->curr);
			}
			edges = edges->next;
		}
	}
}

/*
 ** обнуление посещенности комнат
*/
void	ft_set_null_visited(farm *farm, room ***rooms)
{
	t_node	*deque;
	t_link	*edges;
	int		id;

	deque = ft_new_list(NULL, farm->rooms[farm->id_start]->out);
	while (deque)
	{
		id = ft_get_first(&deque);
		(*rooms)[id]->visited = 0;
		edges = (*rooms)[id]->edges;
		while (edges)
		{
			if ((*rooms)[edges->curr]->visited != 0)
			{
				(*rooms)[edges->curr]->visited = 0;
				ft_add_deque(&deque, edges->curr);
			}
			edges = edges->next;
		}
	}
}