/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:55:25 by vheidy            #+#    #+#             */
/*   Updated: 2020/10/29 14:24:54 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error()
{
	write(1, "Error\n", 6);
	exit(0);
}

char	*ft_check_room(char *str, t_node *(hash_tab)[HT_SIZE])
{
	char			*name;
	long long int	elem_first;
	long long int	elem_sec;
	char			*tmp_space;
	int				len;

	tmp_space = ft_strchr(str, ' ');
	len = ft_strlen(tmp_space);
	name = ft_strsub(str, 0, tmp_space - str);
	while (--len >= 0)
		if (!(tmp_space[len] >= 0 && tmp_space[len] <= 9) && tmp_space[len] != ' ')
			return (NULL);
	elem_first = ft_atoi(tmp_space);
	tmp_space = ft_strchr(tmp_space, ' ');
	elem_sec = ft_atoi(tmp_space);
	if (name[0] == 'L' || elem_first > MAX_INT || \
	elem_first < MIN_INT || elem_sec > MAX_INT || \
	elem_sec < MIN_INT || hash_tab[ft_hasher(name)])
		return (NULL);
	return (name);
}

char	*ft_check_next_room(char *buf, t_node *(hash_tab)[HT_SIZE])
{
	int		red;
	char	*name;

	free(buf);
	if ((red = get_next_line(0, &buf)))
		if ((name = ft_check_room(buf, hash_tab)))
			return (name);
		else
			error();
	else
		error();
}

// void	ft_add_in_hash_tab(char *name, t_node *(hash_tab)[HT_SIZE])
// {
	
// }

int		ft_read(t_node *(hash_tab)[HT_SIZE])
{
	int		red;
	char	*buf;
	char	*start;
	char	*end;
	char	*name;

	while ((red = get_next_line(0, &buf)))
	{
		if (buf[0] == '#')
			if (buf == "##start")
				ft_add_in_hash_tab((start = ft_check_next_room(buf, hash_tab)), hash_tab); // проверяет на валидность следующую строку и возвращает ее имя
			else if (buf == "##end")
				ft_add_in_hash_tab((end = ft_check_next_room(buf, hash_tab)), hash_tab);
		else if ((name = ft_check_room(buf, hash_tab))) /* - возвращает имя комнаты - (проверка на валдиность строки с комнатой) - 
		 проверка на валидность координат, первый символ, и проверка на существование комнаты с таким именем */
			ft_add_in_hash_tab(name, hash_tab); // добавление комнаты в хэш-таблицу  - если по этому индексу уже ест имя, то в след листpslpal
		else
			error();
		free(buf);
	}
	return (0);
}

void	ft_set_null(t_node *(hash_tab)[HT_SIZE])
{
	int	i;

	i = -1;
	while (++i < HT_SIZE)
	{
		hash_tab[i]->name = NULL;
		hash_tab[i]->next =NULL;
	}
}

int		main(int ac, char **av) {
	t_node	hash_tab[HT_SIZE];

	if (ac != 2)
		return (0);
	ft_set_null(&hash_tab);
	// hash_tab[0].name = ft_strdup("123tghyjuikjuyhtgfrtgyhujikujyhgtfrtgyhujkiujhygtfrtgyhujjyhtgrfvtby");
	// printf("%s\n", hash_tab[0].name);
	// if (!(hash_tab))
	ft_read(&hash_tab); // считывает, проверяет на валидность и записывает в хэштаблицу
}