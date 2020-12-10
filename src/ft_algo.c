/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:56:03 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/04 11:29:42 by polina           ###   ########.fr       */
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
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_list(NULL, id);
	}
}

void	ft_support_transform(t_route **res, t_route *tmp_best, \
t_farm *farm, int *count)
{
	int		i;
	int		j;
	t_route	*tmp;

	i = 1;
	tmp = *res;
	while ((tmp)->next)
		tmp = (tmp)->next;
	(tmp)->count_ants = tmp_best->count_ants;
	while (*count < (tmp)->size - 1)
	{
		j = 0;
		while (farm->rooms[j]->in != tmp_best->tops[i])
			j++;
		(tmp)->tops[(*count)++] = j;
		i += 2;
	}
	if (tmp_best->next)
		(tmp)->next = ft_init_route(tmp_best->next->size / 2 + 1, \
		farm->id_start, farm->id_end, 0);
}

/*
 ** переводит бинарные вершины обратно в данные
*/

void	ft_transform_bin_route(t_route **best, t_farm *farm)
{
	t_route	*res;
	t_route	*tmp_best;
	int		count;

	tmp_best = *best;
	count = 1;
	res = ft_init_route(tmp_best->size / 2 + 1, farm->id_start, \
	farm->id_end, 0);
	while (tmp_best)
	{
		count = 1;
		ft_support_transform(&res, tmp_best, farm, &count);
		tmp_best = tmp_best->next;
	}
	ft_del_route(best);
	*best = res;
}

/*
 ** алгоритм нахождения оптимального пути для текущего количества муравьев
 ** проверка на наличие пути от старта к финишу
*/

void	ft_algo(t_farm *farm, t_room ***bin_rooms)
{
	t_node	*deque;
	t_route	*best;

	best = NULL;
	deque = ft_new_list(NULL, farm->rooms[farm->id_start]->out);
	(*bin_rooms)[farm->rooms[farm->id_start]->out]->level = 0;
	while (ft_bfs(&deque, bin_rooms, farm->rooms[farm->id_end]->in))
	{
		while (ft_dfs(bin_rooms, farm->rooms[farm->id_end]->in, \
		farm->rooms[farm->id_start]->out, farm))
			ft_choose_best(&best, bin_rooms, farm);
		ft_set_null_level(farm, bin_rooms);
		ft_del_deque(&deque);
		deque = ft_new_list(NULL, farm->rooms[farm->id_start]->out);
		(*bin_rooms)[farm->rooms[farm->id_start]->out]->level = 0;
	}
	if (!best)
		error_one();
	ft_transform_bin_route(&best, farm);
	ft_move_print_ants(farm, best);
	ft_del_bin_rooms(bin_rooms, (farm->count_rooms * 2 - 2));
	ft_del_farm(farm);
	ft_del_route(&best);
}
