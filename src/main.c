/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:55:25 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/03 19:29:23 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_add_line(t_farm *farm, char **str)
{
	char	**new_output;
	int		i;

	i = -1;
	new_output = NULL;
	if (!farm->output)
	{
		farm->output = malloc(sizeof(char*) * 2);
		farm->output[0] = *str;
		farm->count_str = 2;
		farm->output[1] = NULL;
	}
	else
	{
		new_output = malloc(sizeof(char*) * farm->count_str + 1);
		new_output[farm->count_str] = NULL;
		while ((farm->output)[++i])
			new_output[i] = ft_strdup((farm->output)[i]);
		new_output[i] = *str;
		ft_del_output(&farm->output);
		farm->output = new_output;
		farm->count_str++;
	}
}

void	error_one(void)
{
	write(1, "ERROR\n", 6);
	exit(0);
}

int		ft_hasher(char *name)
{
	int	hash;
	int	c;

	hash = 5381;
	c = *name;
	while (c)
	{
		hash = ((hash << 5) + hash) + c;
		name++;
		c = *name;
	}
	return (hash % HT_SIZE);
}

/*
 ** создание нового листа
*/

t_node	*ft_new_list(char *name, int id)
{
	t_node	*new_list;

	new_list = ft_memalloc(sizeof(t_node));
	new_list->id = id;
	new_list->name = name;
	return (new_list);
}

int		main(void)
{
	t_parse	st;
	t_farm	farm;
	t_room	**binary_rooms;

	binary_rooms = NULL;
	ft_bzero(&st, sizeof(t_parse));
	ft_bzero(&farm, sizeof(farm));
	ft_read(&st, &farm);
	ft_del_st(&st);
	ft_create_binary_tops(&farm, &binary_rooms);
	ft_link_binary_tops(&farm, &binary_rooms);
	ft_algo(&farm, &binary_rooms);
	return (0);
}
