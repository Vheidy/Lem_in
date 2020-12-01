/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polina <polina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 20:44:19 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/01 22:57:00 by polina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 ** проверка на существование уже такого имени (если существет - 0)
*/
int		ft_check_name(t_node *hash_tab[HT_SIZE], char *name)
{
	int	i;
	t_node *tmp;

	i = ft_hasher(name);
	tmp = hash_tab[i];
	if (tmp && !ft_strcmp(tmp->name, name))
		return (0);
	else if (tmp)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, name))
				return (0);
			tmp = tmp->next;
		}
	}
	// if (!ft_strcmp(name, "Hqr7"))
	// 	ft_print_tab(hash_tab);
	// if (!ft_strcmp(name, "Iwa8"))
	// 	printf("here\n");
	return (1);
}

/*
 ** возвращает имя комнаты - (проверка на валдиность строки с комнатой) - 
 ** проверка на валидность координат, первый символ, 
 ** и проверка на существование комнаты с таким именем
*/
char	*ft_check_room(char *str, t_node *hash_tab[HT_SIZE], farm *farm)
{
	char			*name;
	long long int	elem_first;
	long long int	elem_sec;
	char			*tmp_space;
	int				len;

	ft_add_line(farm, &str);
	if (!(tmp_space = ft_strchr(str, ' ')))
		return (NULL);
	len = ft_strlen(tmp_space);
	if (!(name = ft_strsub(str, 0, tmp_space - str)) || name[0] == 'L') // malloc
		error();
	while (--len >= 0){
		if (!(tmp_space[len] >= '0' && \
		tmp_space[len] <= '9') && tmp_space[len] != ' ')
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

/*
 ** проверяет на валидность следующую строку и возвращает ее имя
*/
char	*ft_check_next_room(char **buf, t_node *hash_tab[HT_SIZE], farm *farm)
{
	int		red;
	char	*name;

	name = NULL;
	// printf("%s\n", *buf);
	ft_add_line(farm, buf);
	// ft_print_output(farm);
	if ((red = get_next_line(0, buf)))
	{
	// printf("oooKOKOK\n");
		if (!(name = ft_check_room(*buf, hash_tab, farm)))
			error();
	}
	else
		error();
	return (name);
}

/*
 ** добавление комнаты в хэш-таблицу  
 ** - если по этому индексу уже есть имя, то в след лист
*/
void	ft_add_in_hash_tab(char *name, t_parse *st, int id)
{
	int		index;
	t_node	*tmp;

	index = ft_hasher(name);
	tmp = st->hash_tab[index];
	if (!st->hash_tab[index])
		st->hash_tab[index] = ft_new_list(name, id);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_new_list(name, id);
	}
	st->count_rooms++;
}

/*
 ** считывает комнаты и если видит связь ставит флаг
*/
int		ft_parse_room(t_parse *st, int fl, char **buf, farm *farm)
{
	int		id;
	char	*name;
	int		red;

	id = 0;
	while (!fl && (red = get_next_line(0, buf)))
	{
		// printf("%s\n", *buf);
		if (*buf[0] == '#' && !fl)
		{
			if (!ft_strcmp(*buf, "##start"))
				ft_add_in_hash_tab((st->start = \
				ft_check_next_room(buf, st->hash_tab, farm)), st, id++);
			else if (!ft_strcmp(*buf,  "##end"))
				ft_add_in_hash_tab((st->end = \
				ft_check_next_room(buf, st->hash_tab, farm)), st, id++);
			else
				ft_add_line(farm, buf);
		}
		else if (!fl && (name = ft_check_room(*buf, st->hash_tab, farm)))
			ft_add_in_hash_tab(name, st, id++);
		else if (ft_check_link(*buf, st->hash_tab))
			fl = ft_init_farm(farm, st);
		else
			return (0);
	}
	if (!fl)
		return (0);
	return (1);
}
