/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 18:18:13 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/30 19:15:31 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
		if (id != -1 && id != farm->id_end)
		{
			j = 0;
			while (farm->ants->tops[j] != id)
				j++;
			farm->ants[i].current = farm->ants[i].tops[j + 1];
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
	farm->ants = malloc(sizeof(ant) * farm->count_ants);
	ft_init_ants(farm);
	while (i--)
	{
		tmp = best;
		ft_move_ants(farm); // сдвигаем всех
		while (tmp)
		{
			if (tmp->count_ants)
			{
				farm->ants[index].current = tmp->tops[1];
				farm->ants[index++].tops = tmp->tops;
				tmp->count_ants--;
			}
			tmp = tmp->next;
		}
		ft_print_ants(farm); // вывод какой муравей в какой пизиции
		farm->count_move--;
	}
	while (farm->count_move-- >= 0)
	{
		ft_move_ants(farm);
		ft_print_ants(farm);
	}
}