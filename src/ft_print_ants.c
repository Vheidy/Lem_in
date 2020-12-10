/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 18:18:13 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/04 11:31:06 by polina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_init_ants(t_farm *farm)
{
	int	i;

	i = -1;
	while (++i < farm->count_ants)
		farm->ants[i].current = -1;
}

void	ft_move_ants(t_farm *farm)
{
	int		i;
	int		j;
	int		id;

	i = -1;
	j = 0;
	while (++i < farm->count_ants)
	{
		id = farm->ants[i].current;
		j = 0;
		if (id != -1 && id != farm->id_end)
		{
			while (farm->ants[i].tops[j] != id)
				j++;
			farm->ants[i].current = farm->ants[i].tops[j + 1];
		}
		else if (id == farm->id_end)
			farm->ants[i].current = -1;
	}
}

void	ft_print_ants(t_farm *farm)
{
	int		i;
	t_farm tmp;
	

	i = -1;
	tmp = *farm;
	while (++i < tmp.count_ants)
	{
		if (tmp.ants[i].current != -1)
			ft_printf("L%d-%s ", i + 1, \
			tmp.rooms[tmp.ants[i].current]->name);
	}
	ft_printf("\n");
}

void	ft_support_move_print(t_farm *farm, t_route *best, int *index)
{
	t_route	*tmp;

	tmp = best;
	ft_move_ants(farm);
	while (tmp)
	{
		if (tmp->count_ants)
		{
			farm->ants[*index].current = tmp->tops[1];
			farm->ants[*index].tops = tmp->tops;
			farm->ants[(*index)++].size = tmp->size;
			tmp->count_ants--;
		}
		tmp = tmp->next;
	}
	ft_print_ants(farm);
	farm->count_move--;
}

void	ft_move_print_ants(t_farm *farm, t_route *best)
{
	int		index;
	t_route	*tmp;
	int		i;

	index = 0;
	tmp = best;
	i = -1;
	while (farm->output[++i])
		ft_printf("%s\n", farm->output[i]);
	ft_printf("\n");
	i = farm->count_ants;
	farm->ants = malloc(sizeof(t_ant) * farm->count_ants);
	ft_init_ants(farm);
	while (i--)
		ft_support_move_print(farm, best, &index);
	while (--farm->count_move > 0)
	{
		ft_move_ants(farm);
		ft_print_ants(farm);
	}
}
