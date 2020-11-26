/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:08:57 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/26 19:22:19 by vheidy           ###   ########.fr       */
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
			{
				rooms[tmp->curr]->level = rooms[curr_id]->level + 1;
				return (curr_id);
			}
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
	t_link	*tmp_s;
	int		fl;
	int		i;

	tmp = farm->rooms[id]->edges;
	tmp_s = NULL;
	// fl = 0;
	i = farm->rooms[id]->level + 1;
	// farm->rooms[id]->level = -1;
	// printf("Must del: %d\n", id);
	while (--i > 0)
	{
		fl = 0;
		while (tmp)
		{
			tmp_s = farm->rooms[tmp->curr]->edges;
			while (tmp_s)
			{
				if (tmp_s->curr != id && farm->rooms[tmp_s->curr]->level == farm->rooms[id]->level)
				{
					fl = 1;
					// printf("Del id: %d\n", id);
					farm->rooms[id]->level = -1;
				}
				tmp_s = tmp_s->next;
			}
			if (!fl && farm->rooms[tmp->curr]->level != -1 && \
			farm->rooms[tmp->curr]->level == farm->rooms[id]->level - 1)
			{
				// printf("Del id: %d\n", id);
				farm->rooms[id]->level = -1;
				id = tmp->curr;
				tmp = farm->rooms[id]->edges;
				break;
			}
			tmp = tmp->next;
		}
	}
}

int	ft_form_block_flow(farm *farm, int id)
{
	int		tmp;
	t_link	*edges;

	printf("Curr id: %d\n", id);
	// printf("In: %d\n", farm->rooms[id]->in);
	// printf("Out: %d\n", farm->rooms[id]->out);
	edges = farm->rooms[id]->edges;
	tmp = 0;
	if (id == farm->id_end)
		return (1);
	if (farm->rooms[id]->visited == 1)
		return (0);
	farm->rooms[id]->visited = 1;
	if (farm->rooms[id]->in == 1 && farm->rooms[id]->in_out == 0)
	{
		printf("ok\n");
		farm->rooms[id]->in = 0;
		farm->rooms[id]->out = 1;
	}
	while (edges)
	{
		if (farm->rooms[edges->curr]->visited == 0 && \
		((farm->rooms[id]->out == 1 && edges->flow == 0) \
		|| (farm->rooms[id]->in == 1 && edges->flow == -1)))
		{
			if (id != farm->id_end && farm->rooms[id]->out == 1)
			{
				farm->rooms[edges->curr]->in = 1;
				farm->rooms[edges->curr]->out = 0;
			}
			else if (id != farm->id_end)
			{
				farm->rooms[edges->curr]->in = 0;
				farm->rooms[edges->curr]->out = 1;
			}
			farm->rooms[edges->curr]->level = farm->rooms[id]->level + 1;
			tmp = ft_form_block_flow(farm, edges->curr);
			if (tmp)
				return (1);
		}
		edges = edges->next;
	}
	return (0);
}
// t_route	*ft_form_block_flow(farm *farm)
// {
// 	t_node	*deque;
// 	int		id;
// 	t_link	*edges;
// 	int		fl;
// 	t_route	*res;

// 	edges = NULL;
// 	res = NULL;
// 	deque = ft_new_list(NULL, farm->id_start);
// 	farm->rooms[farm->id_start]->level = 0;
// 	while (deque)
// 	{
// 		// printf("ok\n");
// 		id = ft_get_first(&deque);
// 		edges = farm->rooms[id]->edges;
// 		printf("Curr id: %d\n", id);
// 		fl = 0;
// 		if (farm->rooms[id]->in == 1 && farm->rooms[id]->in_out == 0)
// 		{
// 			farm->rooms[id]->in = 0;
// 			// farm->rooms[id]->in_out = 1;
// 			farm->rooms[id]->out = 1;
// 		}
// 		// printf("In: %d\n", farm->rooms[id]->in);
// 		// printf("Out: %d\n", farm->rooms[id]->out);
// 		while (edges)
// 		{
// 			if (((farm->rooms[id]->out == 1 && edges->flow == 0) \
// 			|| (farm->rooms[id]->in == 1 && edges->flow == -1)) && \
// 			farm->rooms[edges->curr]->level == -1)
// 			{
// 				printf("Neib %d\n", edges->curr);
// 				if (edges->curr == farm->id_end)
// 				{
// 					ft_form_route(&res, id, farm, 0);
// 					// printf("RES: %d\n", id);
// 					return (res);
// 				}
// 				farm->rooms[edges->curr]->level = farm->rooms[id]->level + 1;
// 				if (farm->rooms[id]->out == 1)
// 				{
// 					farm->rooms[edges->curr]->in = 1;
// 					farm->rooms[edges->curr]->out = 0;
// 				}
// 				else
// 				{
// 					farm->rooms[edges->curr]->in = 0;
// 					farm->rooms[edges->curr]->out = 1;
// 				}
// 				ft_add_deque(&deque, edges->curr);
// 				fl = 1;
// 			}
// 			edges = edges->next;
// 		}
// 		if (!fl)
// 			ft_del_waste_route(farm, id);
// 		// printf("Level: %d\n", farm->rooms[id]->level);
// 	}
// 	return (NULL);
// }

void	ft_set_null_level(farm *farm)
{
	t_node	*deque;
	t_link	*edges;
	int		id;

	deque = ft_new_list(NULL, farm->id_start);
	farm->rooms[farm->id_start]->level = -1;
	while (deque)
	{
		id = ft_get_first(&deque);
		edges = farm->rooms[id]->edges;
		while (edges)
		{
			if (farm->rooms[edges->curr]->level != -1)
			{
				farm->rooms[edges->curr]->level = -1;
				ft_add_deque(&deque, edges->curr);
			}
			edges = edges->next;
		}
	}
}

int		ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int		ft_dfs(farm *farm, int id, int flow)
{
	t_link	*edges;
	t_link	*tmp;
	int		pushed;

	edges = farm->rooms[id]->edges;
	tmp = NULL;
	if (id == farm->id_end)
	{
		// printf("end\n");
		return (1);
	}
	if (!flow)
		return (0);
	if (farm->rooms[id]->level == -1)
		return (0);
	while (edges)
	{
		// // printf("Id: %d, neib: %d\n", id, edges->curr);
		// if (farm->rooms[edges->curr]->level == farm->rooms[id]->level + 1 && id == 10 && edges->curr == 13)
		// 	// printf("aga, cap: %d, flow :%d\n", edges->cap, edges->flow);
		// if ((edges->cap - edges->flow > 0) && id == 10)
		// 	// printf("ugu\n");
		if (farm->rooms[edges->curr]->level == farm->rooms[id]->level + 1 \
		&& (edges->cap - edges->flow > 0))
		{
			pushed = ft_dfs(farm, edges->curr);
			if (pushed)
			{
				// printf("ok\n");
				edges->flow += 1;
				tmp = farm->rooms[edges->curr]->edges;
				while (tmp->curr != id)
					tmp = tmp->next;
				tmp->flow -= 1;
				return (pushed);
			}
		}
		edges = edges->next;
	}
	return (0);
}

/*
 ** проверка на наличие пути от старта к финишу
*/
void	ft_algo(farm *farm)
{
	int		id;
	t_route	*best;
	// t_node	*tmp;
	// t_node	*head;
	t_route	*tmp_block_flow;
	// t_route	*add;

	best = NULL;
	tmp_block_flow = NULL;
	// tmp = ft_new_list(NULL, farm->id_end);
	while ((id = ft_bfs(farm->rooms, farm->id_start, farm->id_end)) != -1)
	{
		ft_form_route(&best, farm->id_end, farm, 1);
		ft_set_null_level(farm);
		// ft_print_farm(farm);
		
		int i = -1;
		while (++i < best->size)
			printf("First Top: %d\n", best->tops[i]);
		farm->rooms[farm->id_start]->level = 0;
		if (ft_form_block_flow(farm, farm->id_start) == 1) // defence
		{
			ft_form_route(&tmp_block_flow, farm->id_end, farm, 0);
				i = -1;
			printf("Level end: %d\n", farm->rooms[farm->id_end]->level);
			while (++i < tmp_block_flow->size)
				printf("Top: %d\n", tmp_block_flow->tops[i]);
		}
		// ft_print_farm(farm);
		// {
		// 	i = -1;
		// head = tmp;
		// while (tmp){
		// 	printf("Top: %d\n", tmp->id);
		// 	tmp = tmp->next;
		// }
		ft_set_null_level(farm);
		// printf("ok\n");
		
		// if (ft_compare_flow(best, tmp_block_flow))
		// 	ft_update_farm(farm, best, tmp_block_flow);
	}
	// printf("%d\n", best->size);
	// int i = -1;
	// while (++i < best->size)
	// 	printf("Top: %d\n", best->tops[i]);
	// ft_print_farm(farm);
}
