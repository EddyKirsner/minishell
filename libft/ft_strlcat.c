/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:06:01 by ktaouach          #+#    #+#             */
/*   Updated: 2024/05/28 13:09:21 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	k = ft_strlen(dst) + ft_strlen(src);
	j = 0;
	i = ft_strlen(dst);
	if (size < ft_strlen(dst))
		return (ft_strlen(src) + size);
	size -= i;
	while (size > 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
		size--;
	}
	if (size > 0)
		dst[i] = '\0';
	return (k);
}
