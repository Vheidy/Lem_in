/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:55:25 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/19 16:18:26 by vheidy           ###   ########.fr       */
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
void	ft_set_null(t_parse *st)
{
	int	i;

	i = -1;

	st->start = NULL;
	st->end = NULL;
	st->num_ant = 0;
	st->count_rooms = 0;
	while (++i < HT_SIZE)
	{
		// ft_memdel((void **)&st->hash_tab[i]->name);
		// ft_memdel((void **)&st->hash_tab[i]);
		st->hash_tab[i] = NULL;
	}
}

/*
 ** удаление структуры для парсинга
*/
void	ft_del_st(t_parse *st)
{
	int	i;

	i = -1;
	st->count_rooms = 0;
	st->num_ant = 0;
	ft_memdel((void **)&st->start);
	ft_memdel((void **)&st->end);
	while (++i < HT_SIZE)
	{
		ft_memdel((void **)&st->hash_tab[i]->name);
		ft_memdel((void **)&st->hash_tab[i]);
		st->hash_tab[i] = NULL;
	}
	free(st->hash_tab);
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
