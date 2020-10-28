/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <vheidy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:39:58 by vheidy            #+#    #+#             */
/*   Updated: 2020/10/28 21:34:42 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

# define HT_SIZE 500
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct			s_node
{
	char				*name;
	struct s_node		*next;
}						t_node;

#endif
