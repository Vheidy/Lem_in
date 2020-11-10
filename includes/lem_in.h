/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:58 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/10 14:45:16 by vheidy           ###   ########.fr       */
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

// struct s_room
// {
// 	connections	*neighbors;
// 	int			level;
// };

// typedef struct s_room room;

// struct s_connections
// {
// 	int		count;
// 	room	*rooms;
// };

// typedef struct s_connections connections;

// struct s_ant
// {
// 	room	*current_room;
// 	room	*target_room;
// 	int		id;
// };

// typedef struct s_ant ant;

// struct s_farm
// {
// 	room	*start_room;
// 	room	*target_room;
// 	// ant		*ants;
// 	// ant		**ants;
// 	int		count_ants;
// };

int		ft_read(t_lem *st);
void	error();
int		ft_hasher(char *name);
t_node	*ft_new_list(char *name);

#endif
