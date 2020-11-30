#include "../includes/lem_in.h"

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
 ** обход в ширину
*/
int		ft_bfs(t_node **deque, room ***rooms, int id_end)
{
	t_link	*edges;
	int		curr_id;

	curr_id = 0;
	edges = NULL;
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

void	ft_transform_bin_route(t_route **best, farm *farm, int count)
{
	t_route	*res;
	t_route	*tmp;
	t_route	*tmp_best;
	int		i;
	int		j;

	tmp_best = *best;
	res = ft_init_route(tmp_best->size / 2 + 1, farm->id_start, farm->id_end, 0);
	while (tmp_best)
	{
		i = 1;
		count = 1;
		tmp = res;
		while((tmp)->next)
			tmp = (tmp)->next;
		tmp->count_ants = tmp_best->count_ants;
		while (count < (tmp)->size - 1)
		{
			j = 0;
			while (farm->rooms[j]->in != tmp_best->tops[i])
				j++;
			(tmp)->tops[count++] = j;
			i += 2;
		}
		if (tmp_best->next)
			(tmp)->next = ft_init_route(tmp_best->next->size / 2 + 1, farm->id_start, farm->id_end, 0);
		tmp_best = tmp_best->next;
	}
	ft_del_route(best);
	*best = res;
}

/*
 ** алгоритм нахождения оптимального пути для текущего количества муравьев
 ** проверка на наличие пути от старта к финишу
*/
void	ft_algo(farm *farm, room ***bin_rooms)
{
	t_node	*deque;
	t_route	*best;
	int		count;

	best = NULL;
	count = 0;
	deque = ft_new_list(NULL, farm->rooms[farm->id_start]->out);
	(*bin_rooms)[farm->rooms[farm->id_start]->out]->level = 0;
	while (ft_bfs(&deque, bin_rooms, farm->rooms[farm->id_end]->in))
	{
		while (ft_dfs(bin_rooms, farm->rooms[farm->id_end]->in, farm->rooms[farm->id_start]->out, farm))
			ft_choose_best(&best, bin_rooms, farm);
		ft_set_null_level(farm, bin_rooms);
		ft_del_deque(&deque);
		deque = ft_new_list(NULL, farm->rooms[farm->id_start]->out);
		(*bin_rooms)[farm->rooms[farm->id_start]->out]->level = 0;
	}
	if (!best)
		error();
	ft_transform_bin_route(&best, farm, count);
	ft_move_print_ants(farm, best);
}
