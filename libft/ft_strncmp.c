/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:03:07 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/06 14:05:45 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (n > 1 && s1[i] != '\0')
	{
		if ((unsigned char) s1[i] == (unsigned char) s2[i])
			i++;
		else
			break ;
		n--;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
