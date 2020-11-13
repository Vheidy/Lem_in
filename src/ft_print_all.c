#include "lem_in.h"

/*
 ** выводит хэш-таблицу, временная функция
*/

void	ft_print_tab(t_node *hash_tab[HT_SIZE])
{
	int	i;
	t_node *tmp;

	i = 0;
	while (i < 500)
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

void	ft_print_farm(farm *farm)
{
	int i = 0;
	printf("Count ants: %d\n", farm->count_ants);
	printf("Count rooms: %d\n", farm->count_rooms);
	printf("ID start: %d\n", farm->id_start);
	printf("ID end: %d\n", farm->id_end);
	while (i < farm->count_rooms)
	{
		t_node *tmp;
		// printf("ID: %d\n",farm->rooms[i]->id);
		// printf("ok\n");
		
		printf("Name room: %s\n", farm->rooms[i]->name);
		tmp = farm->rooms[i]->neighbors;
		if (tmp)
		{
			printf("Name neib: %s\n", tmp->name);
			// if (!ft_strcmp(tmp->name, "3"))
			// 	printf("Name neib: %s\n", tmp->next->name);
			while (tmp->next)
			{
				// printf("ok\n");
				tmp = tmp->next;
				printf("Name neib: %s\n", tmp->name);
			}
		}
		printf("----\n");
		// free(tmp);
		i++;
		// printf("ok\n");
	}
}