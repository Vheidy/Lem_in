/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 20:44:19 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/03 18:52:25 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
 ** проверка на существование уже такого имени (если существет - 0)
*/

int		ft_check_name(t_node *hash_tab[HT_SIZE], char *name)
{
	int		i;
	t_node	*tmp;

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
	return (1);
}

char	*ft_check_room(char *str, t_node *hash_tab[HT_SIZE], t_farm *farm)
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
	if (!(name = ft_strsub(str, 0, tmp_space - str)) || name[0] == 'L')
		error_one();
	while (--len >= 0)
		if (!(tmp_space[len] >= '0' && \
		tmp_space[len] <= '9') && tmp_space[len] != ' ')
			return (NULL);
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

char	*ft_check_next_room(char **buf, t_node *hash_tab[HT_SIZE], t_farm *farm)
{
	int		red;
	char	*name;

	name = NULL;
	ft_add_line(farm, buf);
	if ((red = get_next_line(0, buf)))
	{
		if (!(name = ft_check_room(*buf, hash_tab, farm)))
			error_one();
	}
	else
		error_one();
	return (name);
}

void	ft_support_check_room(char **buf, t_parse *st, t_farm *farm, int *id)
{
	if (!ft_strcmp(*buf, "##start"))
		ft_add_in_hash_tab((st->start = \
		ft_check_next_room(buf, st->hash_tab, farm)), st, (*id)++);
	else if (!ft_strcmp(*buf, "##end"))
		ft_add_in_hash_tab((st->end = \
		ft_check_next_room(buf, st->hash_tab, farm)), st, (*id)++);
	else
		ft_add_line(farm, buf);
}

/*
 ** считывает комнаты и если видит связь ставит флаг
*/

int		ft_parse_room(t_parse *st, int fl, char **buf, t_farm *farm)
{
	int		id;
	char	*name;
	int		red;

	id = 0;
	while (!fl && (red = get_next_line(0, buf)))
	{
		if (*buf[0] == '#' && !fl)
			ft_support_check_room(buf, st, farm, &id);
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
