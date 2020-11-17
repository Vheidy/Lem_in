/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:58 by vheidy            #+#    #+#             */
/*   Updated: 2020/11/17 12:55:18 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // del
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
	int					count_rooms;
	char				*start;
	char				*end;
	t_node				*hash_tab[HT_SIZE];
	long long int		num_ant;
}						t_lem;

typedef struct s_room
{
	t_node		*neighbors;
	int			id;
	char		*name;
	int			level;
	int			count_link;
}				room;

// struct s_ant
// {
// 	room	*current_room;
// 	room	*target_room;
// 	int		id;
// };

// typedef struct s_ant ant;

typedef struct s_farm
{
	room	**rooms;
	int		id_start;
	int		id_end;
	// ant		*ants;
	// ant		**ants;
	int		count_rooms;
	int		count_ants;
}				farm;

// void	ft_print_tab(t_node *hash_tab[HT_SIZE]);
// void	ft_print_farm(farm *farm);
void	ft_algo(farm	*farm);
void	ft_read_ants(char **buf, t_lem *st);
int		ft_check_name(t_node *hash_tab[HT_SIZE], char *name);
int		ft_init_farm(farm *farm, t_lem *st);
int		ft_check_link(char *buf, t_node *hash_tab[HT_SIZE]);
t_node	*ft_get_elem(char *name, t_node *hash_tab[HT_SIZE]);
int		ft_parse_room(t_lem *st, int fl, char **buf, farm *farm);
void	ft_parse_link(char *buf, farm *farm, t_lem *st);
int		ft_read(t_lem *st, farm	*farm);
void	error();
int		ft_hasher(char *name);
t_node	*ft_new_list(char *name, int id);

#endif
