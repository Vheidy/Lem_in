/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_best.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:16:57 by polina            #+#    #+#             */
/*   Updated: 2020/12/03 22:13:29 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 ** нахождение оптимального маршрута
*/

t_route	*ft_find_min_route(t_route **route)
{
	t_route	*tmp;
	t_route	*res;

	res = *route;
	tmp = *route;
	// printf("RES ants %d\n", res->count_ants);
	while (tmp)
	{
		if (tmp->size / 2 + tmp->count_ants < res->size / 2 + res->count_ants)
			res = tmp;
		tmp = tmp->next;
	}
	// ft_print_route(res);
	return (res);
}

/*
 ** подсчет количества ходов по каждому из путей для текущего кол-ва муравьев
*/

int		ft_count_move(t_route **route, t_farm *farm)
{
	int		ants;
	t_route	*tmp;
	t_route	*first;

	ants = farm->count_ants;
		
	first = ft_find_min_route(route);
	first->count_ants = 1;
	while (--ants)
	{
		tmp = ft_find_min_route(route);
		tmp->count_ants++;
	}
	printf("C_A %d, SIZE %d\n", tmp->count_ants, tmp->size);
	return (tmp->count_ants + tmp->size / 2);
}

/*
 ** выбор луучшего маршрута между текущим и новым
*/

void	ft_choose_best(t_route **best, t_room ***bin_rooms, t_farm *farm)
{
	t_route	*curr_route;
	int		best_res;
	int		curr_res;

	curr_route = ft_create_route(bin_rooms, farm);
	printf("new\n");
	// ft_print_route(curr_route);
	ft_set_null_visited(farm, bin_rooms);
	if (!*best)
	{
		(*best) = curr_route;
		(*best)->count_ants = farm->count_ants;
		farm->count_move = (*best)->size / 2 + (*best)->count_ants;
	}
	else
	{
		best_res = ft_count_move(best, farm);
		curr_res = ft_count_move(&curr_route, farm);
		printf("Curr %d, best %d\n", curr_res, best_res);
		if (curr_res < best_res)
		{
			farm->count_move = curr_res;
			ft_del_route(best);
			(*best) = curr_route;
		}
		else
			ft_del_route(&curr_route);
	}
}
