/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:58 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/03 21:39:29 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include "../ft_printf/includes/ft_printf.h"

# define HT_SIZE 500
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct		s_node
{
	char			*name;
	int				id;
	struct s_node	*next;
}					t_node;

typedef struct		s_parse
{
	int				count_rooms;
	char			*start;
	char			*end;
	t_node			*hash_tab[HT_SIZE];
	long long int	num_ant;
}					t_parse;

typedef struct		s_link
{
	int				parent;
	int				curr;
	int				flow;
	int				cap;
	struct s_link	*next;
}					t_link;

typedef struct		s_room
{
	t_link			*edges;
	int				in;
	int				out;
	int				id;
	char			*name;
	int				level;
	int				visited;
}					t_room;

typedef struct		s_route
{
	int				size;
	int				*tops;
	int				count_ants;
	struct s_route	*next;
}					t_route;

typedef struct		s_ant
{
	int				current;
	int				*tops;
	int				size;
	int				id;
}					t_ant;

typedef struct		s_farm
{
	t_room			**rooms;
	int				id_start;
	int				id_end;
	char			**output;
	int				count_str;
	int				count_move;
	t_ant			*ants;
	int				count_rooms;
	int				count_ants;
}					t_farm;

void	ft_print_farm(t_farm *farm); //DEL!!
void	ft_print_route(t_route *route);
void	ft_print_bin_rooms(t_room ***bin_rooms, t_farm *farm);

void				ft_del_st(t_parse *st);
void				ft_del_output(char ***output);
void				ft_del_bin_rooms(t_room ***bin_rooms, int size);
void				ft_del_output(char ***output);
void				ft_del_farm(t_farm *farm);
void				ft_del_link(t_link **edges);
void				ft_del_deque(t_node **deque);
void				ft_del_route(t_route **route);
void				ft_set_null_level(t_farm *farm, t_room ***rooms);
void				ft_set_null_visited(t_farm *farm, t_room ***rooms);

void				ft_move_print_ants(t_farm *farm, t_route *best);
void				ft_add_line(t_farm *farm, char **str);

void				ft_choose_best(t_route **best, t_room ***bin_rooms, \
t_farm *farm);

void				ft_add_deque(t_node **deque, int id);
int					ft_get_first(t_node **deque);
int					ft_bfs(t_node **deque, t_room ***rooms, int id_end);
int					ft_dfs(t_room ***rooms, int id_end, int id, t_farm *farm);
void				ft_algo(t_farm *farm, t_room ***bin_rooms);

t_route				*ft_init_route(int size, int id_first, int id_last, int fl);
t_route				*ft_create_route(t_room ***bin_rooms, t_farm *farm);
int					ft_check_one_top(t_farm *farm, int id_f, int id_s);
void				ft_create_binary_tops(t_farm *farm, t_room ***binary_rooms);
void				ft_link_binary_tops(t_farm *farm, t_room ***bin_rooms);

t_room				*ft_create_room(int id, char *name);
char				*ft_check_next_room(char **buf, t_node *hash_tab[HT_SIZE], \
t_farm *farm);
void				ft_read_ants(char **buf, t_parse *st, t_farm *farm);
int					ft_check_name(t_node *hash_tab[HT_SIZE], char *name);
int					ft_check_link(char *buf, t_node *hash_tab[HT_SIZE]);
t_node				*ft_get_elem(char *name, t_node *hash_tab[HT_SIZE]);

int					ft_parse_room(t_parse *st, int fl, char **buf, \
t_farm *farm);
void				ft_parse_link(char *buf, t_farm *farm, t_parse *st);
int					ft_read(t_parse *st, t_farm	*farm);

void				error_one();
t_node				*ft_new_list(char *name, int id);
int					ft_init_farm(t_farm *farm, t_parse *st);
t_link				*ft_new_link(int id_f, int id_s, int cap);

int					ft_hasher(char *name);
void				ft_add_in_hash_tab(char *name, t_parse *st, int id);

#endif
