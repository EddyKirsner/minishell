/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:29:23 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/08 14:15:02 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
	size_t	count_digits(int n)
{
	unsigned int	count;
	char			flip;

	if (n == 0)
		return (1);
	flip = 0;
	count = 0;
	if (n < 0)
	{
		if (n == -2147483648)
			n = -2147483647;
		n *= -1;
		flip = 1;
	}
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	if (n > 0)
		count++;
	if (flip > 0)
		return (count + 1);
	return (count);
}

static
	void	convert(int n, char *str)
{
	unsigned int	siz;

	siz = count_digits(n);
	str[siz] = '\0';
	siz--;
	while (siz > 0)
	{
		str[siz] = (n % 10) + 48;
		n /= 10;
		siz--;
	}
	str[siz] = (n % 10) + 48;
}

char	*ft_itoa(int n)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc((count_digits(n) + 1) * (sizeof(char)));
	if (res == NULL)
		return (NULL);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = -147483648;
			i++;
			res[1] = '2';
		}
		res[0] = '-';
		n *= -1;
		i++;
	}
	convert(n, &res[i]);
	return (res);
}
