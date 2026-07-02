/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:26:56 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/05 14:53:16 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	siz;
	size_t	half;

	siz = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	half = ft_strlen((char *)s1) + 1;
	res = malloc(siz * (sizeof(char)));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, (char *)s1, half);
	ft_strlcpy(&res[half - 1], (char *)s2, (ft_strlen((char *)s2) + 1));
	return (res);
}
