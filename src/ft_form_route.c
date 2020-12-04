/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_form_route.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:08:41 by polina            #+#    #+#             */
/*   Updated: 2020/12/04 11:32:44 by polina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 ** заполнение потоком маршрута
*/

void	ft_full_route(t_route **route, t_room **bin_rooms, t_farm *farm)
{
	int		i;
	int		id;
	t_link	*edges;
	t_route	*tmp;

	i = 0;
	edges = NULL;
	tmp = *route;
	while ((tmp)->next)
	{
		(tmp) = (tmp)->next;
	}
	id = (tmp)->tops[1];
	while (id != farm->rooms[farm->id_end]->in)
	{
		edges = bin_rooms[id]->edges;
		while (edges->flow != 1)
			edges = edges->next;
		(tmp)->tops[++i + 1] = edges->curr;
		id = edges->curr;
	}
	(tmp)->size = i + 2;
}

/*
 ** вспомогательная функция для создания маршрута
*/

void	ft_support_create_route(t_link *edges, t_room ***bin_rooms, \
t_farm *farm, t_route **res)
{
	t_route	*tmp;

	tmp = *res;
	if (!*res)
	{
		*res = ft_init_route(((*bin_rooms)[farm->rooms[farm->id_end]->in]->level \
		+ 1), farm->rooms[farm->id_start]->out, edges->curr, 1);
	}
	else
	{
		while ((tmp)->next)
			(tmp) = (tmp)->next;
		(tmp)->next = ft_init_route((*bin_rooms)[farm->rooms[farm->id_end]->in]->level \
		+ 1, farm->rooms[farm->id_start]->out, edges->curr, 1);
	}
	(*bin_rooms)[edges->curr]->visited = 1;
	ft_full_route(res, *bin_rooms, farm);
}

/*
 ** создание пути
*/

t_route	*ft_create_route(t_room ***bin_rooms, t_farm *farm)
{
	t_route	*res;
	t_link	*edges;

	res = NULL;
	edges = (*bin_rooms)[farm->rooms[farm->id_start]->out]->edges;
	while (edges)
	{
		if (edges->flow == 1 && (*bin_rooms)[edges->curr]->visited == 0)
			ft_support_create_route(edges, bin_rooms, farm, &res);
		edges = edges->next;
	}
	return (res);
}

/*
 ** проверка относятся ли две вершины к инпуту и аутпуту одной комнаты
*/

int		ft_check_one_top(t_farm *farm, int id_f, int id_s)
{
	int	i;

	i = -1;
	while (++i < farm->count_rooms)
	{
		if (farm->rooms[i]->in == id_f || farm->rooms[i]->out == id_f)
		{
			if (farm->rooms[i]->in == id_f)
			{
				if (farm->rooms[i]->out == id_s)
					return (1);
			}
			else if (farm->rooms[i]->out == id_f)
			{
				if (farm->rooms[i]->in == id_s)
					return (1);
			}
			else
				return (0);
		}
	}
	return (0);
}
