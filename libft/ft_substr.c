/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:24:46 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/08 14:15:55 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
	size_t	true_len(char const *str, size_t len)
{
	size_t	i;

	i = 0;
	while (str[i] && len)
	{
		i++;
		len--;
	}
	if (i == 4294967295)
		return (i);
	return (i + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	siz;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		res = malloc(sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	siz = true_len(&s[start], len);
	res = malloc((siz) * (sizeof(char)));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, (char *)&s[start], siz);
	return (res);
}
