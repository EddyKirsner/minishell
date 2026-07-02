/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:02:01 by ktaouach          #+#    #+#             */
/*   Updated: 2024/05/29 14:48:26 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	if (little == NULL)
		return ((char *)big);
	if (little[i] == '\0')
		return ((char *)big);
	little_len = ft_strlen((char *)little);
	while (len > 0 && big[i] != '\0' && little_len <= len)
	{
		if (big[i] == little[0])
			if (ft_strncmp((char *)&big[i], (char *)little, little_len) == 0)
				return ((char *)&big[i]);
		i++;
		len--;
	}
	return (NULL);
}
