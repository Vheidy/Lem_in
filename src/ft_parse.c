/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:41 by vheidy            #+#    #+#             */
/*   Updated: 2020/10/31 14:35:03 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// проверка на существование уже такого имени

int		ft_check_name(t_node *hash_tab[HT_SIZE], char *name)
{
	int	i;
	t_node *tmp;

	i = ft_hasher(name);
	tmp = hash_tab[i];
	if (tmp && !ft_strcmp(tmp->name, name))
			error();
	else if (tmp)
	{
		while (tmp->next)
		{
			if (!ft_strcmp(tmp->name, name))
				error();
			tmp = tmp->next;
		}
	}
	return (1);
}

/* - возвращает имя комнаты - (проверка на валдиность строки с комнатой) - 
 проверка на валидность координат, первый символ, и проверка на существование комнаты с таким именем */

char	*ft_check_room(char *str, t_node *hash_tab[HT_SIZE])
{
	char			*name;
	long long int	elem_first;
	long long int	elem_sec;
	char			*tmp_space;
	int				len;

	tmp_space = ft_strchr(str, ' ');
	len = ft_strlen(tmp_space);
	if (!(name = ft_strsub(str, 0, tmp_space - str))) // malloc
		error();
	while (--len >= 0){
		if (!(tmp_space[len] >= '0' && tmp_space[len] <= '9') && tmp_space[len] != ' ')
			return (NULL);
	}
	elem_first = ft_atoi(tmp_space);
	tmp_space = ft_strchr(tmp_space, ' ');
	elem_sec = ft_atoi(tmp_space);
	if (name[0] == 'L' || elem_first > MAX_INT || \
	elem_first < MIN_INT || elem_sec > MAX_INT || \
	elem_sec < MIN_INT || !ft_check_name(hash_tab, name))
		return (NULL);
	return (name);
}

 // проверяет на валидность следующую строку и возвращает ее имя

char	*ft_check_next_room(char *buf, t_node *hash_tab[HT_SIZE])
{
	int		red;
	char	*name;

	name = NULL;
	free(buf);
	if ((red = get_next_line(0, &buf)))
	{
		if (!(name = ft_check_room(buf, hash_tab)))
			error();
	}
	else
		error();
	return (name);
}

/* добавление комнаты в хэш-таблицу  
- если по этому индексу уже есть имя, то в след лист */

void	ft_add_in_hash_tab(char *name, t_node *hash_tab[HT_SIZE])
{
	int		index;
	t_node	*tmp;

	index = ft_hasher(name);
	tmp = hash_tab[index];
	if (!hash_tab[index])
	{
		hash_tab[index] = malloc(sizeof(t_node));
		hash_tab[index]->name = name;
		hash_tab[index]->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_list(name);
	}
}

int		ft_read(t_node *hash_tab[HT_SIZE])
{
	int		red;
	char	*buf;
	char	*start;
	char	*end;
	char	*name;

	while ((red = get_next_line(0, &buf)))
	{
		if (buf[0] == '#')
		{
			if (!ft_strcmp(buf,  "##start"))
				ft_add_in_hash_tab((start = ft_check_next_room(buf, hash_tab)), hash_tab);
			else if (!ft_strcmp(buf,  "##end"))
				ft_add_in_hash_tab((end = ft_check_next_room(buf, hash_tab)), hash_tab);
		}
		else if ((name = ft_check_room(buf, hash_tab)))
			ft_add_in_hash_tab(name, hash_tab);
		else
			error();
		free(buf);
	}
	return (0);
}