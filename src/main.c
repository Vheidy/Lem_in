/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:55:25 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/13 18:40:52 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error()
{
	write(1, "ERROR\n", 6);
	exit(0);
}

/*
 ** функция хэширования - принимает имя и возвращает индукс в хэш-таблице
*/
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
	return (hash % 500);
}

/*
 ** создание нового листа
*/
t_node	*ft_new_list(char *name, int id)
{
	t_node	*new_list;

	new_list = malloc(sizeof(t_node));
	new_list->next = NULL;
	new_list->id = id;
	new_list->name = name;
	return (new_list);
}

/*
 ** выставление на нул всех параметров в структуре
*/
void	ft_set_null(t_lem *st)
{
	int	i;

	i = -1;
	st->start = NULL;
	st->end = NULL;
	st->num_ant = 0;
	st->count_rooms = 0;
	while (++i < HT_SIZE)
		st->hash_tab[i] = NULL;
}

int		main() {
	t_lem	st;
	farm	farm;

	ft_set_null(&st);
	ft_read(&st, &farm);
	return (0);
}
