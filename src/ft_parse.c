/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:41 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/10 14:47:29 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* Задачи:
Добавить проверку на нужный порядок (количество муравьев - комнаты - связи) - DONE
Проверка на существование комнат в линках
Добавить создание и запись в файл для вывода в конце
Добавить считывание из хэш-таблицы в новые структуры
Добавить считывание линков в новые структуры
Инициализация новых структур

Итог:
Должна быть полностью считана и записана в структуры ферма 
и создан файл для дальнейшего вывода
Проверка на существование пути от старта к финишу (при bfs)
*/

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
 проверка на валидность координат, первый символ, 
 и проверка на существование комнаты с таким именем */

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

void	ft_add_in_hash_tab(char *name, t_node *hash_tab[HT_SIZE], int id)
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
	tmp->id = id;
}

// проверка строки с линком на валидность и добавление его в список смежности

// int		ft_check_link(char *buf, t_node *hash_tab[HT_SIZE])
// {
// 	char	*name_f;
// 	char	*name_s;
// 	char	*tmp;
// 	char	*end;
	
// 	if (!(tmp = ft_strchr(buf, '-')))
// 		return (0);
// 	end = buf;
// 	while (*end)
// 		end++;
// 	if (!(name_f = ft_strsub(buf, 0, tmp - buf)) || \
// 	!(name_s = ft_strsub(buf, tmp - buf + 1, end - tmp))) // malloc * 2
// 		return (0);
// 	if (!(ft_check_name(hash_tab, name_f) && \
// 	ft_check_name(hash_tab, name_s)))
// 		return (0);
	
// }

int		ft_parse_room(t_lem *st, int *fl, char *buf)
{
	int		id;
	char	*name;

	id = 0;
	if (buf[0] == '#' && !(*fl))
	{
		if (!ft_strcmp(buf,  "##start"))
			ft_add_in_hash_tab((st->start = \
			ft_check_next_room(buf, st->hash_tab)), st->hash_tab, id++);
		else if (!ft_strcmp(buf,  "##end"))
			ft_add_in_hash_tab((st->end = \
			ft_check_next_room(buf, st->hash_tab)), st->hash_tab, id++);
	}
	else if ((name = ft_check_room(buf, st->hash_tab)) && !(*fl))
		ft_add_in_hash_tab(name, st->hash_tab, id++);
	// else if (ft_add_check_link(buf, st->hash_tab))
	// 	return (*fl = 1);
	else
		return (0);
	return (1);
}

// void	ft_parse(t_lem *st, int red, char *buf, char *name)
// {

// 	while ((red = get_next_line(0, &buf)))
// 	{
// 		if (!ft_parse_room(st, red, *buf, name) || \
// 		!ft_add_check_link(buf, st->hash_tab))
// 			error();
// 		free(buf);
// 	}
// }

// общая функция считывания - считывает количество элементов и 
// передает дальше для считывания комнат и связей

int		ft_read(t_lem *st)
{
	int		red;
	char	*buf;
	int		fl;

	fl = 0;
	if ((red = get_next_line(0, &buf)))
	{
		if (!(st->num_ant = ft_atoi(buf)))
			error();
		free(buf);
		while ((red = get_next_line(0, &buf)))
		{
			if (!ft_parse_room(st, &fl, buf))
				error();
			free(buf);
		}
	}
	else
		error();
	return (0);
}