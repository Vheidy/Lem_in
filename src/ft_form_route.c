/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_form_route.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:08:41 by polina            #+#    #+#             */
/*   Updated: 2020/11/26 16:50:45 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 ** ищет среди соседей нужный и проставлет поток 
 ** нужна чтобы не дублировать код
*/
void	ft_find_next(int id_first, int id_sec, farm *farm, int filler)
{
	t_link	*tmp;

	tmp = farm->rooms[id_first]->edges;
	while (tmp->curr != id_sec)
		tmp = tmp->next;
	tmp->flow = filler;
}

/*
 ** заполнение пути 1 и -1
*/
void	ft_full_for_route(t_route **route, farm *farm)
{
	int		i;

	i = -1;
	// printf("ok\n");
	// printf("%d\n", route->size);
	while (++i + 1 < (*route)->size)
	{
		if ((*route)->tops[i] != farm->id_start)
		{
			farm->rooms[(*route)->tops[i]]->in_out = 1;
		}
		ft_find_next((*route)->tops[i], (*route)->tops[i + 1], farm, 1);
		ft_find_next((*route)->tops[i + 1], (*route)->tops[i], farm, -1);
	}
}

/*
 ** инициализация маршрута - проставляет старт и енд и малочит под вершины
*/
t_route	**ft_init_route(t_route **route, room *tmp_room, farm *farm)
{
	t_route	**tmp;

	tmp = route;
	if (!*tmp)
		*tmp = malloc(sizeof(t_route));
	else
	{
		while ((*tmp)->next)
			(*tmp) = (*tmp)->next;
		(*tmp)->next = malloc(sizeof(t_route));
		(*tmp) = (*tmp)->next;
	}
	(*tmp)->next = NULL;
	(*tmp)->size = tmp_room->level + 1;
	(*tmp)->tops = malloc(sizeof(int) * (*tmp)->size);
	(*tmp)->tops[0] = farm->id_start;
	// (*tmp)->tops[tmp_room->level + 1] = farm->id_end;
	return (tmp);
}

/*
 ** создание пути и проставление потоков (flow)
*/
void	ft_form_route(t_route **route, int id, farm *farm, int fl)
{
	int		i;
	room	*tmp_room;
	t_link	*tmp_link;
	t_route	**tmp;

	tmp_room = farm->rooms[id];
	i = tmp_room->level + 1;
	// printf("ID: %d\n", id);
	printf("Level: %d\n", tmp_room->level);
	tmp = ft_init_route(route, tmp_room, farm);
	printf("Size: %d\n",( *tmp)->size);
	while (--i > 0)
	{
		(*tmp)->tops[i] = id;
		// printf("%d\n", id); 
		tmp_link = tmp_room->edges;
		// printf("Level: %d\n", farm->rooms[id]->level);
		while (farm->rooms[tmp_link->curr]->level != tmp_room->level - 1)
			tmp_link = tmp_link->next;
		// farm->rooms[id]->level = 0;
		// while (!fl && (farm->rooms[tmp_link->curr]->visited != tmp_room->visited - 1))
		// 	tmp_link = tmp_link->next;
		id = farm->rooms[tmp_link->curr]->id;
		tmp_room = farm->rooms[id];
	}
	if (fl)
		ft_full_for_route(route, farm);
}
