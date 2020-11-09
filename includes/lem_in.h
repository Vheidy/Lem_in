/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:58 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/03 18:01:02 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

# define HT_SIZE 500
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct			s_node
{
	char				*name;
	int					id;
	struct s_node		*next;
}						t_node;

typedef struct			s_lem
{
	char				*start;
	char				*end;
	t_node				*hash_tab[HT_SIZE];
	long long int		num_ant;
}						t_lem;


int		ft_read(t_lem *st);
void	error();
int		ft_hasher(char *name);
t_node	*ft_new_list(char *name);

#endif
