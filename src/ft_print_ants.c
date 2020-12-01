/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 18:18:13 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/01 21:47:34 by polina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_print_tops(int *tops, int size)
{
	int i;

	i = -1;
	printf("TOPS\n");
	while (++i < size)
		printf("%d\n", tops[i]);
}

void	ft_init_ants(farm *farm)
{
	int	i;

	i = -1;
	while (++i < farm->count_ants)
		farm->ants[i].current = -1;
}

void	ft_move_ants(farm *farm)
{
	int		i;
	int		j;
	int		id;

	i = -1;
	j = 0;
	while (++i < farm->count_ants)
	{
		id = farm->ants[i].current;
		// printf("ID %d\n", id);
		j = 0;
		if (id != -1 && id != farm->id_end)
		{
		// printf("id ants %d, room name %s, room id %d\n", i + 1, farm->rooms[farm->ants[i].current]->name, farm->ants[i].current);
			// ft_print_tops(farm->ants[i].tops, farm->ants[i].size);
			while (farm->ants[i].tops[j] != id)
				j++;
			// printf("J %d\n", j);
			// printf("ID before %d, id next %d\n", farm->ants->tops[j], farm->ants->tops[j + 1]);
			farm->ants[i].current = farm->ants[i].tops[j + 1];
		// printf("id ants %d, room name %s, room id %d\n", i + 1, farm->rooms[farm->ants[i].current]->name, farm->ants[i].current);
		}
		else if (id == farm->id_end)
			farm->ants[i].current = -1;
	}
}

void	ft_print_ants(farm *farm)
{
	int		i;
	int		fl;

	i = -1;
	
	while (++i < farm->count_ants)
	{
		fl = 0;
		// printf("Curr %d\n", farm->ants[i].current);
		if (farm->ants[i].current != -1)
		{
			
			printf("L%d-%s", i + 1, farm->rooms[farm->ants[i].current]->name);
			fl = 1;
		}
		if (fl)
			printf(" ");
	}
	// if (fl)
		printf("\n");
}



void	ft_move_print_ants(farm *farm, t_route *best)
{
	int	index;
	t_route	*tmp;
	int	i;

	index = 0;
	tmp = best;
	i = farm->count_ants;
	// printf("%d\n", farm->count_move);
	farm->ants = malloc(sizeof(ant) * farm->count_ants);
	ft_init_ants(farm);
	while (i--)
	{
		tmp = best;
		ft_move_ants(farm); // сдвигаем всех
		while (tmp)
		{
			// printf("tmp->count_ants %d\n", tmp->count_ants);
			if (tmp->count_ants)
			{
				farm->ants[index].current = tmp->tops[1];
				farm->ants[index].tops = tmp->tops;
				farm->ants[index++].size = tmp->size;
				// printf("Index ant %d, curr name  %s\n", index, farm->rooms[farm->ants[index - 1].current]->name);
				// ft_print_tops(farm->ants[index - 1].tops, tmp->size);
				tmp->count_ants--;
				// farm->count_move--;
			}
			tmp = tmp->next;
		}
		ft_print_ants(farm); // вывод какой муравей в какой пизиции
		farm->count_move--;
	}
	while (--farm->count_move > 0)
	{
		ft_move_ants(farm);
		ft_print_ants(farm);
	}
}