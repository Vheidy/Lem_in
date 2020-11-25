/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asybil <asybil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:54:53 by asybil            #+#    #+#             */
/*   Updated: 2020/11/26 00:07:29 by asybil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/string_utils.h"

static	char	*join(char const *s1, char const *s2)
{
	int	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	return (ft_strcat(ft_strcpy(ft_strnew(len), s1), s2));
}

void			init_string(void)
{
	ft_bzero(&g_input, sizeof(t_string));
}

void			string_append_line(char *str)
{
	char	*line;
	char	*old_input;
	int		len;

	line = join(str, "\n");
	old_input = g_input.str;
	g_input.str = join(g_input.str, line);
	ft_strdel(&line);
	ft_strdel(&old_input);
	g_input.len = ft_strlen(g_input.str);
}

void			print_string(void)
{
	write(1, g_input.str, g_input.len);
	ft_strdel(&g_input.str);
}
