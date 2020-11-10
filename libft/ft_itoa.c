/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheidy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:04:28 by vheidy            #+#    #+#             */
/*   Updated: 2019/09/18 16:20:37 by vheidy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len(int n)
{
	int len;

	len = 0;
	if (n < 0)
		len++;
	while (n >= 10 || n <= -10)
	{
		len++;
		n = n / 10;
	}
	len++;
	return (len);
}

static char		ft_iter(int n)
{
	char i;

	if (n >= 0)
		i = n % 10 + '0';
	if (n < 0)
		i = n % 10 * -1 + '0';
	return (i);
}

char			*ft_itoa(int n)
{
	char	*s2;
	int		len;

	len = ft_len(n);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (s2 == NULL)
		return (0);
	s2[len--] = '\0';
	while (n >= 10 || n <= -10)
	{
		s2[len--] = ft_iter(n);
		n = n / 10;
	}
	s2[len] = ft_iter(n);
	if (n < 0)
		s2[len - 1] = '-';
	return (s2);
}
