#include "../../includes/lem_in.h"

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
			printf("I %d\n", i);
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
void	ft_print_farm(farm *farm)
{
	int i = 0;
	printf("PRINT FARM\n");
	printf("Count ants: %d\n", farm->count_ants);
	printf("Count rooms: %d\n", farm->count_rooms);
	printf("ID start: %d\n", farm->id_start);
	printf("ID end: %d\n", farm->id_end);
	while (i < farm->count_rooms)
	{
		t_link *tmp;
		printf("Name room: %s\n", farm->rooms[i]->name);
		printf("ID room: %d\n", farm->rooms[i]->id);
		// printf("Level room: %d\n", farm->rooms[i]->level);
		printf("In room: %d\n", farm->rooms[i]->in);
		printf("Out room: %d\n", farm->rooms[i]->out);
		// printf("In_out room: %d\n", farm->rooms[i]->in_out);
		tmp = farm->rooms[i]->edges;
		if (tmp)
		{
			printf("Name neib: %s\n", farm->rooms[tmp->curr]->name);
			
			// if (!ft_strcmp(tmp->name, "3"))
			printf("Flow neib: %d\n", tmp->flow);
			// printf("Cap neib: %d\n", tmp->cap);
			while (tmp->next)
			{
				// printf("ok\n");
				tmp = tmp->next;
				printf("Name neib: %s\n", farm->rooms[tmp->curr]->name);
				printf("Flow neib: %d\n", tmp->flow);
				// printf("Cap neib: %d\n", tmp->cap);
				// printf("In_out neib: %d\n", tmp->in_out);
			}
		}
		printf("----\n");
		// free(tmp);
		i++;
		// printf("ok\n");
	}
}

void	ft_print_binary_tops(room **bin_room, farm *farm)
{
	int i = -1;

	while (++i < (farm->count_rooms * 2 - 2))
	{
		t_link *tmp;
		// printf("oooooooK\n");
		// printf("%d\n", i);
		printf("ID room: %d\n", bin_room[i]->id);
		printf("Level room: %d\n", bin_room[i]->level);
		// printf("Id neib: %d\n", bin_room[i]->edges->curr);
		tmp = bin_room[i]->edges;
		if (tmp)
		{
			printf("Id neib: %d, Cap: %d, Flow: %d\n", tmp->curr, tmp->cap, tmp->flow);
			while (tmp->next)
			{
				tmp = tmp->next;
				printf("Id neib: %d, Cap: %d, Flow: %d\n", tmp->curr, tmp->cap, tmp->flow);
			}
		}
		printf("----\n");
	}
}

void	ft_print_route(t_route **route, farm *farm)
{
	int i = -1;
	t_route *tmp = *route;

	// printf("ТУЦ\n");
	while (tmp)
	{
		i = -1;
		printf("Count_ants %d\n", tmp->count_ants);
		while (++i < tmp->size)
			printf("Top: %s\n", farm->rooms[tmp->tops[i]]->name);
		tmp = tmp->next;
		printf("---------\n");
	}
		printf("---------\n");
}

void	ft_print_output(farm *farm)
{
	int i = -1;

	printf("OUTPUT\n");
	printf("Size output %d\n", farm->count_str);
	while (farm->output[++i])
		printf("%s\n", farm->output[i]);
}