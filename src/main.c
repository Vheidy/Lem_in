/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:55:25 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/30 17:58:52 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_del_output(char ***output)
{
	char	**tmp;
	int i = 0;

	tmp = *output;
	while (tmp[i])
		free(tmp[i++]);
	free(*output);
}

void	ft_add_line(farm *farm, char **str)
{
	char **new_output;
	int	i;

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
			new_output[i] = (farm->output)[i];
		new_output[i] = *str;
		free(farm->output);
		farm->output = new_output;
		farm->count_str++;
	}
}

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

// /*
//  ** удаление структуры для парсинга
// */
// void	ft_del_st(t_parse *st)
// {
// 	int	i;
// 	t_node	*tmp;
// 	t_node	*tmp_s;

// 	i = -1;
// 	tmp = NULL;
// 	tmp_s = NULL;
// 	printf("--- %s\n", st->hash_tab[347]->name);
// 	st->count_rooms = 0;
// 	st->num_ant = 0;
// 	ft_memdel((void **)&st->start);
// 	ft_memdel((void **)&st->end);
// 	while (++i < HT_SIZE)
// 	{
// 		if (st->hash_tab[i])
// 		{
// 			printf("%d\n", i);
// 			tmp = st->hash_tab[i];
// 			while (tmp)
// 			{
// 				tmp_s = tmp->next;
// 				ft_memdel((void **)&tmp->name);
// 				ft_memdel((void **)&tmp);
// 				tmp = tmp_s;
// 			}
// 			tmp = NULL;
// 		}
// 	}
// 	// free(st->hash_tab);
// }

int		main() {
	t_parse	st;
	farm	farm;
	room	**binary_rooms;

	// ft_set_null(&st);
	binary_rooms = NULL;
	ft_bzero(&st, sizeof(t_parse));
	ft_bzero(&farm, sizeof(farm));
	// printf("oooKOKOK\n");
	ft_read(&st, &farm);
	// ft_print_output(&farm);
	// ft_print_tab(st.hash_tab);
	// ft_print_farm(&farm);
	ft_create_binary_tops(&farm, &binary_rooms);
	ft_link_binary_tops(&farm, &binary_rooms);
	ft_algo(&farm, &binary_rooms);
	return (0);
}
