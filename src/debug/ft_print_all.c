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
	printf("Count ants: %d\n", farm->count_ants);
	printf("Count rooms: %d\n", farm->count_rooms);
	printf("ID start: %d\n", farm->id_start);
	printf("ID end: %d\n", farm->id_end);
	while (i < farm->count_rooms)
	{
		t_link *tmp;
		printf("Name room: %s\n", farm->rooms[i]->name);
		printf("ID room: %d\n", farm->rooms[i]->id);
		printf("Level room: %d\n", farm->rooms[i]->level);
		// printf("In room: %d\n", farm->rooms[i]->in);
		// printf("Out room: %d\n", farm->rooms[i]->out);
		printf("In_out room: %d\n", farm->rooms[i]->in_out);
		tmp = farm->rooms[i]->edges;
		if (tmp)
		{
			printf("Name neib: %s\n", farm->rooms[tmp->curr]->name);
			
			// if (!ft_strcmp(tmp->name, "3"))
			printf("Flow neib: %d\n", tmp->flow);
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