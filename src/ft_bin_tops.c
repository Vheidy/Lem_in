/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_tops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:29:35 by polina            #+#    #+#             */
/*   Updated: 2020/12/03 18:55:49 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 ** добавляет линки к бинарникам
*/

void	ft_add_bin_link(t_room ***rooms, int id_first, int id_sec, \
int cap)
{
	t_link *tmp;

	tmp = (*rooms)[id_first]->edges;
	if (!tmp)
		(*rooms)[id_first]->edges = ft_new_link(id_first, id_sec, cap);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_link(id_first, id_sec, cap);
	}
}

/*
 ** создает инпут и аутпут как отдельные комнаты
*/

void	ft_create_in_out(int i, t_room ***bin_rooms, \
t_farm *farm, int *binary_id)
{
	t_room	*new_room;

	if (i != farm->id_start)
	{
		new_room = ft_create_room(*binary_id, NULL);
		(*bin_rooms)[*binary_id] = new_room;
		(*bin_rooms)[*binary_id]->id = *binary_id;
		farm->rooms[i]->in = (*binary_id)++;
	}
	if (i != farm->id_end)
	{
		new_room = ft_create_room(*binary_id, NULL);
		(*bin_rooms)[*binary_id] = new_room;
		(*bin_rooms)[*binary_id]->id = *binary_id;
		farm->rooms[i]->out = (*binary_id)++;
	}
}

/*
 ** раздваивает вершины по инпутам и аутпутам
*/

void	ft_create_binary_tops(t_farm *farm, t_room ***binary_rooms)
{
	int	i;
	int	binary_id;

	i = -1;
	binary_id = 0;
	if (!(*binary_rooms = malloc(sizeof(t_room*) \
	* (farm->count_rooms * 2) - 2)))
		error_one();
	while (++i < farm->count_rooms)
	{
		ft_create_in_out(i, binary_rooms, farm, &binary_id);
		if (farm->rooms[i]->in != -1 && farm->rooms[i]->out != -1)
			ft_add_bin_link(binary_rooms, \
			farm->rooms[i]->in, farm->rooms[i]->out, 1);
	}
}

/*
 ** добавление связи между ин и аут с проставление капэсити
*/

void	ft_add_link_between_inout(t_farm *farm, \
t_room ***bin_rooms, int fl, int i)
{
	t_link	*edges;

	edges = NULL;
	edges = farm->rooms[i]->edges;
	while (edges)
	{
		if (!fl)
		{
			if (farm->rooms[edges->curr]->out != -1)
				ft_add_bin_link(bin_rooms, farm->rooms[i]->in, \
				farm->rooms[edges->curr]->out, 0);
		}
		else if (farm->rooms[edges->curr]->in != -1)
			ft_add_bin_link(bin_rooms, farm->rooms[i]->out, \
			farm->rooms[edges->curr]->in, 1);
		edges = edges->next;
	}
}

/*
 ** добавление связи между ин и аут
*/

void	ft_link_binary_tops(t_farm *farm, t_room ***bin_rooms)
{
	int		i;
	t_link	*edges;

	i = -1;
	edges = NULL;
	while (++i < farm->count_rooms)
	{
		if (farm->rooms[i]->in != -1)
			ft_add_link_between_inout(farm, bin_rooms, 0, i);
		if (farm->rooms[i]->out != -1)
			ft_add_link_between_inout(farm, bin_rooms, 1, i);
	}
}
