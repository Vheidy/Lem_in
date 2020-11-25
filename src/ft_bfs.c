/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:08:57 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/23 16:02:53 by polina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
int		ft_bfs(room **rooms, int id_start, int id_end)
{
	t_link	*tmp;
	int		curr_id;
	t_node	*deque;

	tmp = 0;
	curr_id = 0;
	deque = ft_new_list(NULL, id_start);
	rooms[id_start]->level = 0;
	while (deque)
	{
		curr_id = ft_get_first(&deque);
		tmp = rooms[curr_id]->edges;
		while (tmp)
		{
			if (tmp->curr == id_end)
				return (curr_id);
			if (rooms[tmp->curr]->in_out == 0 && rooms[tmp->curr]->level == -1)
			{
				rooms[tmp->curr]->level = rooms[curr_id]->level + 1;
				ft_add_deque(&deque, tmp->curr);
			}
			tmp = tmp->next;
		}
	}
	return (-1);
}

void	ft_del_waste_route(farm *farm, int id)
{
	t_link	*tmp;

	tmp = farm->rooms[id]->edges;
	while (!(farm->rooms[tmp->curr]->visited == farm->rooms[id]->visited && \
	tmp->curr != id))
	{
		while (tmp)
		{
			if (farm->rooms[tmp->curr]->visited == farm->rooms[id]->visited - 1)
			{
				farm->rooms[tmp->curr]->visited = 0;
				id = tmp->curr;
				tmp = farm->rooms[id]->edges;
				break;
			}
			tmp = tmp->next;
		}
	}
}

t_route	*ft_form_block_flow(farm *farm)
{
	t_node	*deque;
	int		id;
	t_link	*tmp;
	int		fl;
	t_route	*res;

	tmp = NULL;
	res = NULL;
	deque = ft_new_list(NULL, farm->id_start);
	farm->rooms[farm->id_start]->visited = 0;
	while (deque)
	{
		id = ft_get_first(&deque);
		tmp = farm->rooms[id]->edges;
		fl = 0;
		if (farm->rooms[id]->in == 1 && farm->rooms[id]->in_out == 0)
		{
			farm->rooms[id]->in = 0;
			farm->rooms[id]->in_out = 1;
			farm->rooms[id]->out = 1;
		}
		while (tmp)
		{
			if (tmp->curr == farm->id_end)
			{
				ft_form_route(&res, id, farm, 0);
				return (res);
			}
			if ((farm->rooms[id]->out == 1 && tmp->flow == 0) \
			|| (farm->rooms[id]->in == 1 && tmp->flow == -1))
			{
				farm->rooms[tmp->curr]->visited = farm->rooms[id]->visited + 1;
				if (farm->rooms[id]->out == 1)
					farm->rooms[tmp->curr]->in = 1;
				else
					farm->rooms[tmp->curr]->out = 1;
				ft_add_deque(&deque, tmp->curr);
				fl = 1;
			}
			tmp = tmp->next;
		}
		if (!fl)
			ft_del_waste_route(farm, id);
	}
	return (NULL);
}

/*
 ** проверка на наличие пути от старта к финишу
*/
void	ft_algo(farm *farm)
{
	int		id;
	t_route	*best;
	t_route	*tmp_block_flow;
	// t_route	*add;

	best = NULL;
	// tmp_block_flow = NULL;
	while ((id = ft_bfs(farm->rooms, farm->id_start, farm->id_end)) != -1)
	{
		// printf("%d\n", id);
		ft_form_route(&best, id, farm, 1);
		int i = -1;
		while (++i < best->size)
			printf("First Top: %d\n", best->tops[i]);
		// ft_print_farm(farm);
		tmp_block_flow = ft_form_block_flow(farm);
		i = -1;
		while (++i < tmp_block_flow->size)
			printf("Top: %d\n", tmp_block_flow->tops[i]);
		// if (ft_compare_flow(best, tmp_block_flow))
		// 	ft_update_farm(farm, best, tmp_block_flow);
	}
	// printf("%d\n", best->size);
	// int i = -1;
	// while (++i < best->size)
	// 	printf("Top: %d\n", best->tops[i]);
	// ft_print_farm(farm);
}
