#include "lem_in.h"

/*
 ** выводит хэш-таблицу, временная функция
*/
void	ft_print_tab(t_node *hash_tab[HT_SIZE])
{
	int	i;
	t_node *tmp;

	i = 0;
	tmp = 0;
	while (i < HT_SIZE)
	{
		if (hash_tab[i])
		{
			tmp = hash_tab[i];
			printf("Name %s\n", tmp->name);
			printf("ID %d\n", tmp->id);
			while (tmp->next)
			{
				printf("%s\n", tmp->name);
				printf("ID %d\n", tmp->id);
				tmp = tmp->next;
			}
		}
		i++;
	}
}

/*
 ** Выводит ферму и линки
*/
void	ft_print_farm(t_farm *farm)
{
	int i = 0;
	printf("Count ants: %d\n", farm->count_ants);
	printf("Count rooms: %d\n", farm->count_rooms);
	printf("ID start: %d\n", farm->id_start);
	printf("ID end: %d\n", farm->id_end);
	while (i < farm->count_rooms)
	{
		t_link *tmp;
		printf("Name room: %s\n", farm->rooms[i]->name);
		// printf("Level room: %d\n", farm->rooms[i]->level);
		printf("ID room: %d\n", farm->rooms[i]->id);
		tmp = farm->rooms[i]->edges;
		if (tmp)
		{
			printf("Name neib: %s\n", farm->rooms[tmp->curr]->name);
			// printf("Flow neib: %d\n", tmp->flow);
			// if (!ft_strcmp(tmp->name, "3"))
			// 	printf("Name neib: %s\n", tmp->next->name);
			while (tmp->next)
			{
				// printf("ok\n");
				tmp = tmp->next;
				printf("Name neib: %s\n", farm->rooms[tmp->curr]->name);
				// printf("Flow neib: %d\n", tmp->flow);
			}
		}
		printf("----\n");
		// free(tmp);
		i++;
		// printf("ok\n");
	}
}


void	ft_print_bin_rooms(t_room ***bin_rooms, t_farm *farm)
{
	int i = 0;
	while (i < farm->count_rooms * 2 - 2)
	{
		t_link *tmp;
		printf("ID bin room: %d\n", (*bin_rooms)[i]->id);
		tmp = (*bin_rooms)[i]->edges;
		if (tmp)
		{
			printf("ID neib: %d\n", tmp->curr);
			printf("Flow neib: %d\n", tmp->flow);
			// if (!ft_strcmp(tmp->name, "3"))
			// 	printf("Name neib: %s\n", tmp->next->name);
			while (tmp->next)
			{
				// printf("ok\n");
				tmp = tmp->next;
				printf("ID neib: %d\n", tmp->curr);
				printf("Flow neib: %d\n", tmp->flow);
			}
		}
		printf("----\n");
		// free(tmp);
		i++;
		// printf("ok\n");
		printf("---------\n");
	}
}

void	ft_print_route(t_route *route)
{
	int i = -1;
	t_route *tmp;

	tmp = route;
	while(tmp)
	{
		i = -1;
	printf("SIZE %d\n", route->size);
		while (++i < tmp->size)
		{
			printf("%d\n", tmp->tops[i]);
		}
		tmp = tmp->next;
	}
	printf("----\n");
}

