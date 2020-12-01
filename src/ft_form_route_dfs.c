/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_form_route_dfs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:08:41 by polina            #+#    #+#             */
/*   Updated: 2020/12/01 22:22:10 by polina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 ** инициализация маршрута - проставляет старт и енд и малочит под вершины
*/
t_route	*ft_init_route(int size, int id_first, int id_last, int fl)
{
	t_route	*tmp;

	// if (!fl)
	// 	printf("ok\n");
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

// /*
//  ** инициализация маршрута - проставляет старт и енд и малочит под вершины
// */
// t_route	*ft_init_route(farm *farm, room **bin_rooms, int id)
// {
// 	t_route	*tmp;

// 	tmp = malloc(sizeof(t_route));
// 	(tmp)->next = NULL;
// 	(tmp)->size = bin_rooms[farm->rooms[farm->id_end]->in]->level + 1;
// 	(tmp)->tops = malloc(sizeof(int) * (tmp)->size);
// 	(tmp)->tops[0] = farm->rooms[farm->id_start]->out;
// 	(tmp)->tops[1] = id;
// 	(tmp)->count_ants = 0;
// 	return (tmp);
// }

/*
 ** заполнение потоком маршрута
*/
void	ft_full_route(t_route **route, room **bin_rooms, farm *farm)
{
	int		i;
	int		id;
	t_link	*edges;
	t_route	*tmp;

	i = 0;
	edges = NULL;
	tmp = *route;
	while ((tmp)->next)
			(tmp) = (tmp)->next;
	id = (tmp)->tops[1];
	while (id != farm->rooms[farm->id_end]->in)
	{
		edges = bin_rooms[id]->edges;
		while (edges->flow != 1)
			edges = edges->next;
		(tmp)->tops[++i + 1] = edges->curr;
		id = edges->curr;
	}
	tmp->size = i + 2;
}

/*
 ** вспомогательная функция для создания маршрута
*/
void	ft_support_create_route(t_link *edges, room **bin_rooms, farm *farm, t_route **res)
{
	t_route	*tmp;

	tmp = NULL;
	if (edges->flow == 1 && bin_rooms[edges->curr]->visited == 0)
	{
		tmp = *res;
		if (!*res)
			*res = ft_init_route(bin_rooms[farm->rooms[farm->id_end]->in]->level + 1, \
			farm->rooms[farm->id_start]->out, edges->curr, 1);
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = ft_init_route(bin_rooms[farm->rooms[farm->id_end]->in]->level + 1, \
			farm->rooms[farm->id_start]->out, edges->curr, 1);
		}
		bin_rooms[edges->curr]->visited = 1;
		ft_full_route(res, bin_rooms, farm);
	}
}

/*
 ** создание пути
*/
t_route	*ft_create_route(room **bin_rooms, farm *farm)
{
	t_route	*res;
	t_link	*edges;

	res = NULL;
	edges = bin_rooms[farm->rooms[farm->id_start]->out]->edges;
	while (edges)
	{
		ft_support_create_route(edges, bin_rooms, farm, &res);
		edges = edges->next;
	}
	// ft_print_route(&res, farm);
	return (res);
}

/*
 ** проверка относятся ли две вершины к инпуту и аутпуту одной комнаты
*/
int		ft_check_one_top(farm *farm, int id_f, int id_s)
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

/*
 ** вспомогательная функция для обхода в глубину
*/
void	ft_full_flow_dfs(room ***rooms, t_link *edges, farm *farm, int id)
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
int		ft_dfs(room ***rooms, int id_end, int id, farm *farm)
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
