/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:55:25 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/10 14:44:55 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error()
{
	write(1, "Error\n", 6);
	exit(0);
}

// функция хэширования - принимает имя и возвращает индукс в хэш-таблице

int		ft_hasher(char *name)
{
	int	hash = 5381;
	int	c;

	c = *name;
	while (c)
	{
		hash = ((hash << 5) + hash) + c;
		name++;
		c = *name;
	}
	return (hash % 500);
}

// создание нового листа

t_node	*ft_new_list(char *name)
{
	t_node	*new_list;

	new_list = malloc(sizeof(t_node));
	new_list->next = NULL;
	new_list->name = name;
	return (new_list);
}

// выставление на нул всех параметров в листе

void	ft_set_null(t_node *hash_tab[HT_SIZE])
{
	int	i;

	i = -1;
	while (++i < HT_SIZE)
		hash_tab[i] = NULL;
}

// выводит хэш-таблицу, временная функция

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
			printf("%s\n", tmp->name);
			while (tmp->next)
			{
				tmp = tmp->next;
				printf("%s\n", tmp->name);
			}
		}
		i++;
	}
}

int		main() {
	// t_node	*hash_tab[HT_SIZE];
	t_lem	st;

	// if (ac != 2)
	// 	return (0);
	// hash_tab = malloc(sizeof(t_node));
	// t_lem.num_ant = 0;
	ft_set_null(st.hash_tab);
	// printf("--ok--\n");
	ft_read(&st); // считывает, проверяет на валидность и записывает в хэштаблицу
	ft_print_tab(st.hash_tab); // 
}