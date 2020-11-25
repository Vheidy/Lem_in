/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asybil <asybil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:55:23 by asybil            #+#    #+#             */
/*   Updated: 2020/11/25 23:23:21 by asybil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H

# include "lem_in.h"

/*
**		String Structure
*/
typedef struct	s_string
{
	size_t		len;
	char		*str;
}				t_string;

t_string		g_input;

void			init_string(void);
void			string_append_line(char *str);
void			print_string(void);

#endif
