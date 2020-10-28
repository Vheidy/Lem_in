/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:26:13 by vheidy            #+#    #+#             */
/*   Updated: 2019/09/11 19:13:31 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*temp;

	i = 0;
	temp = (char*)s;
	while (temp[i] != c && temp[i] != '\0')
		i++;
	if (temp[i] == '\0' && c != '\0')
		return (NULL);
	return (&temp[i]);
}
