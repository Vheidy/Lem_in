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

int		ft_bfs(t_node **deque, room **rooms, int id_start, int id_end)
{
	t_link	*edges;
	int		curr_id;

	curr_id = 0;
	edges = NULL;
	while (*deque)
	{
		curr_id = ft_get_first(deque);
		printf("Curr_id: %d\n", curr_id);
		edges = rooms[curr_id]->edges;
		while (edges)
		{
			if (edges->curr == id_end)
			{
				rooms[edges->curr]->level = rooms[curr_id]->level + 1;
				return (1);
			}
			if (rooms[edges->curr]->level == -1 && \
			(edges->cap - edges->flow > 0))
			{
				printf("Neib: %d\n", edges->curr);
				rooms[edges->curr]->level = rooms[curr_id]->level + 1;
				ft_add_deque(deque, edges->curr);
			}
			edges = edges->next;
		}
	}
	return (0);
}
int		ft_dfs(farm *farm, int id)
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
	// if (!flow)
	// 	return (0);
	// if (farm->rooms[id]->level == -1)
		// return (0);
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

void	ft_set_null_level(farm *farm)
{
	t_node	*deque;
	t_link	*edges;
	int		id;

	deque = ft_new_list(NULL, farm->id_start);
	// farm->rooms[farm->id_start]->level = -1;
	while (deque)
	{
		id = ft_get_first(&deque);
		farm->rooms[id]->level = -1;
		// printf("Id %d\n", id);
		edges = farm->rooms[id]->edges;
		while (edges)
		{
			if (farm->rooms[edges->curr]->level != -1)
			{
				// printf("Neib %d\n", edges->curr);
				farm->rooms[edges->curr]->level = -1;
				ft_add_deque(&deque, edges->curr);
			}
			edges = edges->next;
		}
	}
}

void	ft_del_deque(t_node **deque)
{
	t_node	*tmp;
	t_node	*next;

	tmp = *deque;
	next = NULL;
	while (tmp)
	{
		printf("%d\n", tmp->id);
		next = tmp->next;
		// free(tmp->name);
		free(tmp);
		tmp = next;
		if (!tmp)
			printf("nuuull\n");
	}
	*deque = NULL;
}

/*
 ** проверка на наличие пути от старта к финишу
*/
void	ft_algo(farm *farm)
{
	t_node	*deque;
	t_route	*best;

	deque = ft_new_list(NULL, farm->id_start);
	farm->rooms[farm->id_start]->level = 0;
	while (ft_bfs(&deque, farm->rooms, farm->id_start, farm->id_end))
	{
		// ft_bfs(&deque, farm->rooms, farm->id_start, farm->id_end);
		// while (ft_dfs(farm, farm->id_start))
		// 	best = ft_choose_best(best, farm);
		ft_dfs(farm, farm->id_start);
		// if (ft_dfs(farm, farm->id_start))
		// {
		// 	printf("FIRST\n");
		// printf("----------\n---------\n");
		// }
			// ft_check_best()
		ft_set_null_level(farm);
		ft_del_deque(&deque);
		deque = ft_new_list(NULL, farm->id_start);
		farm->rooms[farm->id_start]->level = 0;
		// printf("SECOND\n");
		// ft_bfs(&deque, farm->rooms, farm->id_start, farm->id_end);
		// ft_print_farm(farm);
		// while (ft_dfs(farm, farm->id_start))
		// 	best = ft_choose_best(best, farm);
		// if (ft_dfs(farm, farm->id_start))
		// {
			// printf("SECOND\n");
		// ft_print_farm(farm);
		// printf("----------\n---------\n");
		// }
		// if (ft_compare_arm, best, tmp_block_flow);
	}
}