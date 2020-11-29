/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_best.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:16:57 by polina            #+#    #+#             */
/*   Updated: 2020/11/29 23:47:38 by polina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 ** нахождение оптимального маршрута
*/
t_route	*ft_find_min_route(t_route **route)
{
	t_route	*tmp;
	t_route	*res;

	res = *route;
	tmp = *route;
	while (tmp)
	{
		if (tmp->size + tmp->count_ants < res->size + res->count_ants)
			res = tmp;
		tmp = tmp->next;
	}
	// printf("ok\n");
	// printf("Res size %d\n", res->size);
	return (res);
}
/*
 ** подсчет количества ходов по каждому из путей для текущего кол-ва муравьев
*/
int		ft_count_move(t_route **route, farm *farm)
{
	int		ants;
	t_route	*tmp;
	t_route	*first;

	ants = farm->count_ants;
	// printf("Size route %d\n", (*route)->size);
	first = ft_find_min_route(route);
	first->count_ants++;
	while (--ants)
	{
		tmp = ft_find_min_route(route);
		tmp->count_ants++;
	}
	return (first->count_ants + first->size / 2 + 1);
}

/*
 ** выбор луучшего маршрута между текущим и новым
*/
void	ft_choose_best(t_route **best, room ***bin_rooms, farm *farm)
{
	t_route	*curr_route;
	int		best_res;
	int		curr_res;

	curr_route = ft_create_route(*bin_rooms, farm);
	ft_set_null_visited(farm, bin_rooms);
	if (!*best)
		(*best) = curr_route;
	else
	{
		
		best_res = ft_count_move(best, farm);
		curr_res = ft_count_move(&curr_route, farm);
		if (curr_res < best_res)
		{
			ft_del_route(best);
			(*best) = curr_route;
		}
	}
}