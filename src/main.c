/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:55:25 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/25 17:46:21 by vheidy           ###   ########.fr       */
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
	t_node	*tmp;
	t_node	*tmp_s;

	i = -1;
	tmp = NULL;
	tmp_s = NULL;
	printf("--- %s\n", st->hash_tab[347]->name);
	st->count_rooms = 0;
	st->num_ant = 0;
	ft_memdel((void **)&st->start);
	ft_memdel((void **)&st->end);
	while (++i < HT_SIZE)
	{
		if (st->hash_tab[i])
		{
			printf("%d\n", i);
			tmp = st->hash_tab[i];
			while (tmp)
			{
				tmp_s = tmp->next;
				ft_memdel((void **)&tmp->name);
				ft_memdel((void **)&tmp);
				tmp = tmp_s;
			}
			tmp = NULL;
		}
	}
	// free(st->hash_tab);
}

void	ft_init_in_out(farm *farm)
{
	farm->rooms[farm->id_start]->out = 1;
	farm->rooms[farm->id_start]->in = 0;
	farm->rooms[farm->id_start]->in_out = 1;
	farm->rooms[farm->id_end]->in = 1;
	farm->rooms[farm->id_end]->out = 0;
	farm->rooms[farm->id_end]->in_out = 1;
}

int		main() {
	t_parse	st;
	farm	farm;

	// ft_set_null(&st);
	ft_bzero(&st, sizeof(t_parse));
	ft_read(&st, &farm);
	// ft_print_tab(st.hash_tab);
	ft_init_in_out(&farm);
	// ft_print_farm(&farm);
	// printf("ok\n");
	// ft_del_st(&st); ??!!
	// printf("ok\n");
	// ft_memdel(&(&st));
	// ft_print_farm(&farm);
	// ft_set_null(&st);
	ft_algo(&farm);
	return (0);
}
