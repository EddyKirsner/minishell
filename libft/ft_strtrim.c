/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:50:54 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/08 14:15:26 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
	size_t	trim(char const *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_strchr(set, s1[i]))
			i++;
		else
			break ;
	}
	return (i);
}

static
	size_t	rev_trim(char const *s1, char const *set)
{
	unsigned int	len;

	len = ft_strlen(s1);
	if (!len)
		return (0);
	len--;
	while (len)
	{
		if (ft_strchr(set, s1[len]))
			len--;
		else
			break ;
	}
	return (len + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*res;
	unsigned int	start;
	unsigned int	end;
	size_t			siz;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = trim(s1, set);
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	end = rev_trim(s1, set);
	siz = (end + 1) - (start + 1);
	siz++;
	res = malloc((siz) * (sizeof(char)));
	if (!res)
		return (NULL);
	ft_strlcpy(res, &s1[start], siz);
	return (res);
}
