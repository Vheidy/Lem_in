/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs_and_dfs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:12:12 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/03 19:28:34 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 ** обход в ширину
*/

int		ft_bfs(t_node **deque, t_room ***rooms, int id_end)
{
	t_link	*edges;
	int		curr_id;

	curr_id = 0;
	while (*deque)
	{
		curr_id = ft_get_first(deque);
		edges = (*rooms)[curr_id]->edges;
		while (edges)
		{
			if (edges->curr == id_end)
			{
				(*rooms)[edges->curr]->level = (*rooms)[curr_id]->level + 1;
				return (1);
			}
			if ((*rooms)[edges->curr]->level == -1 && \
			(edges->cap - edges->flow > 0))
			{
				(*rooms)[edges->curr]->level = (*rooms)[curr_id]->level + 1;
				ft_add_deque(deque, edges->curr);
			}
			edges = edges->next;
		}
	}
	return (0);
}

/*
 ** вспомогательная функция для обхода в глубину
*/

void	ft_full_flow_dfs(t_room ***rooms, t_link *edges, t_farm *farm, int id)
{
	t_link	*tmp;

	tmp = NULL;
	edges->flow += 1;
	if (!ft_check_one_top(farm, id, edges->curr))
	{
		tmp = (*rooms)[edges->curr]->edges;
		while (tmp->curr != id)
			tmp = tmp->next;
		tmp->flow -= 1;
	}
}

/*
 ** обход в глубину
*/

int		ft_dfs(t_room ***rooms, int id_end, int id, t_farm *farm)
{
	t_link	*edges;
	int		pushed;

	edges = (*rooms)[id]->edges;
	if (id == id_end)
		return (1);
	while (edges)
	{
		if ((*rooms)[edges->curr]->level == (*rooms)[id]->level + 1 \
		&& (edges->cap - edges->flow > 0))
		{
			pushed = ft_dfs(rooms, id_end, edges->curr, farm);
			if (pushed)
			{
				ft_full_flow_dfs(rooms, edges, farm, id);
				return (pushed);
			}
		}
		edges = edges->next;
	}
	return (0);
}
