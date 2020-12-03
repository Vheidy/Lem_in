/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_null_and_del.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:19:27 by polina            #+#    #+#             */
/*   Updated: 2020/12/03 19:29:19 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_del_farm(t_farm *farm)
{
	int		i;
	t_room	*tmp;

	i = -1;
	ft_del_output(&farm->output);
	free(farm->ants);
	i = -1;
	while (++i < farm->count_rooms)
	{
		tmp = farm->rooms[i];
		ft_strdel(&tmp->name);
		ft_del_link(&tmp->edges);
		free(tmp->edges);
		free(tmp);
	}
	free(farm->rooms);
}

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
		free(tmp->tops);
		free(tmp);
		tmp = next;
	}
	*route = NULL;
}

/*
 ** обнуление слоев
*/

void	ft_set_null_level(t_farm *farm, t_room ***rooms)
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

void	ft_set_null_visited(t_farm *farm, t_room ***rooms)
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
