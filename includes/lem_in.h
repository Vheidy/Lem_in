/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:58 by vheidy            #+#    #+#             */
/*   Updated: 2020/12/02 20:38:14 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../ft_printf/includes/ft_printf.h"

# define HT_SIZE 500
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct			s_node
{
	char				*name;
	int					id;
	struct s_node		*next;
}						t_node;

typedef struct			s_parse
{
	int					count_rooms;
	char				*start;
	char				*end;
	t_node				*hash_tab[HT_SIZE];
	long long int		num_ant;
}						t_parse;

typedef struct s_link
{
	int				parent;
	int				curr;
	int				flow;
	int				cap;
	struct s_link	*next;
}				t_link;


typedef struct s_room
{
	t_link		*edges;
	int			in;
	int			out;
	int			id;
	char		*name;
	int			level;
	int			visited;
}				room;

typedef struct		s_route
{
	int				size;
	int				*tops;
	int				count_ants;
	struct s_route	*next;
}					t_route;


typedef struct s_ant
{
	int	current;
	int	*tops;
	int	size;
	int		id;
}				ant;

// typedef struct s_ant ant;


typedef struct s_farm
{
	room	**rooms;
	int		id_start;
	int		id_end;
	char	**output;
	int		count_str;
	int		count_move;
	// ant		*ants;
	ant		*ants;
	int		count_rooms;
	int		count_ants;
}				farm;

void	ft_del_st(t_parse *st);
void	ft_del_output(char ***output);
void	ft_del_bin_rooms(room ***bin_rooms, int size);
void	ft_del_output(char ***output);
void	ft_del_farm(farm *farm);
void	ft_del_link(t_link **edges);

void	ft_move_print_ants(farm *farm, t_route *best);
void	ft_add_line(farm *farm, char **str);
t_route	*ft_init_route(int size, int id_first, int id_last, int fl);
void	ft_create_binary_tops(farm *farm, room ***binary_rooms);
void	ft_link_binary_tops(farm *farm, room ***bin_rooms);
void	ft_add_deque(t_node **deque, int id);
int		ft_get_first(t_node **deque);
int		ft_dfs(room ***rooms, int id_end, int id, farm *farm);
t_route	*ft_create_route(room **bin_rooms, farm *farm);
void	ft_choose_best(t_route **best, room ***bin_rooms, farm *farm);
void	ft_del_deque(t_node **deque);
void	ft_del_route(t_route **route);
void	ft_set_null_level(farm *farm, room ***rooms);
void	ft_set_null_visited(farm *farm, room ***rooms);
// void	ft_add_link(farm *farm, int id_first, int id_sec, int cap);
room	*ft_create_room(int id, char *name);
// void	ft_form_route(t_route **route, int id, farm *farm);
t_link	*ft_new_link(int id_f, int id_s, int cap);
void	ft_algo(farm *farm, room ***bin_rooms);
void	ft_read_ants(char **buf, t_parse *st, farm *farm);
int		ft_check_name(t_node *hash_tab[HT_SIZE], char *name);
int		ft_init_farm(farm *farm, t_parse *st);
int		ft_check_link(char *buf, t_node *hash_tab[HT_SIZE]);
t_node	*ft_get_elem(char *name, t_node *hash_tab[HT_SIZE]);
int		ft_parse_room(t_parse *st, int fl, char **buf, farm *farm);
void	ft_parse_link(char *buf, farm *farm, t_parse *st);
int		ft_read(t_parse *st, farm	*farm);
void	error_one();
int		ft_hasher(char *name);
t_node	*ft_new_list(char *name, int id);

/*
** Debug functions
*/
// void	ft_print_tab(t_node *hash_tab[HT_SIZE]);
// void	ft_print_farm(farm *farm);
// void	ft_print_binary_tops(room **bin_room, farm *farm);
// void	ft_print_route(t_route **route);
void	ft_print_output(farm *farm);

#endif
