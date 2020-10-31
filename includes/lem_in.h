/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:58 by vheidy            #+#    #+#             */
/*   Updated: 2020/10/31 14:32:24 by vheidy           ###   ########.fr       */
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
	struct s_node		*next;
}						t_node;

int		ft_read(t_node *hash_tab[HT_SIZE]);
void	error();
int		ft_hasher(char *name);
t_node	*ft_new_list(char *name);

#endif
