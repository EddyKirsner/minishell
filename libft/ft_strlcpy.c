/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:36:53 by ktaouach          #+#    #+#             */
/*   Updated: 2024/05/28 11:44:01 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	while (siz > 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		siz--;
		i++;
	}
	if (siz > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}
