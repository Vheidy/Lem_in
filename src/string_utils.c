/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asybil <asybil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:54:53 by asybil            #+#    #+#             */
/*   Updated: 2020/11/25 23:20:07 by asybil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/string_utils.h"

void	init_string(void)
{
	ft_bzero(&g_input, sizeof(t_string));
}

void	string_append_line(char *str)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	tmp = g_input.str;
	len = ft_strlen(str);
	g_input.len += len;
	g_input.str = ft_strcat(ft_strcpy(ft_strnew(g_input.len + 1), g_input.str)\
																		, str);
	if (g_input.str == NULL)
	{
		g_input.len = 0;
		return ;
	}
	g_input.str[g_input.len - 1] = '\n';
}

void	print_string(void)
{
	write(1, g_input.str, g_input.len);
}
