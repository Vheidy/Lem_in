/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 20:29:10 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/02 20:33:50 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_del_link(t_link **edges)
{
	t_link	*next;
	t_link	*head;

	next = NULL;
	head = *edges;
	while ((*edges))
	{
		next = (*edges)->next;
		free(*edges);
		*edges = next;
	}
}

void	ft_del_bin_rooms(room ***bin_rooms, int size)
{
	int		i;
	room	*tmp;

	i = -1;
	while (++i < size)
	{
		tmp = (*bin_rooms)[i];
		ft_del_link(&tmp->edges);
		free(tmp);
	}
	free(*bin_rooms);
}

void	ft_del_output(char ***output)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = *output;
	while (tmp[i])
		free(tmp[i++]);
	free(*output);
}

/*
 ** удаление структуры для парсинга
*/

void	ft_del_st(t_parse *st)
{
	int		i;
	t_node	*tmp;
	t_node	*tmp_s;

	i = -1;
	tmp = NULL;
	tmp_s = NULL;
	st->count_rooms = 0;
	st->num_ant = 0;
	while (++i < HT_SIZE)
	{
		if (st->hash_tab[i])
		{
			tmp = st->hash_tab[i];
			while (tmp)
			{
				tmp_s = tmp->next;
				if (tmp->name)
					ft_strdel(&tmp->name);
				free(tmp);
				tmp = tmp_s;
			}
		}
	}
}
