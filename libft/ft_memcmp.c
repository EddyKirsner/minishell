/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:58:36 by ktaouach          #+#    #+#             */
/*   Updated: 2024/05/22 13:16:28 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				ret;
	unsigned int	original_n;

	original_n = n;
	ret = 0;
	while (n > 0)
	{
		ret = ft_strncmp((char *)s1, (char *) s2, 1);
		if (ret > 0)
			return (original_n);
		if (ret < 0)
			return (-1);
		n--;
		s1++;
		s2++;
	}
	return (ret);
}
