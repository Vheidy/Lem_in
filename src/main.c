/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asybil <asybil@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:55:25 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/21 19:20:10 by asybil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

/*
 ** выставление на нул всех параметров в структуре
*/
void	ft_set_null(t_parse *st)
{
	ft_bzero(st, sizeof(st));
}

int		main() {
	t_parse	st;
	farm	farm;

	ft_set_null(&st);
	ft_read(&st, &farm);
	// ft_del_st(&st);
	ft_print_farm(&farm);
	ft_set_null(&st);
	ft_algo(&farm);
	return (0);
}
