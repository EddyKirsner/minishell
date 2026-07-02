/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:15:22 by ktaouach          #+#    #+#             */
/*   Updated: 2024/05/30 13:22:45 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*res;

	res = malloc((ft_strlen(src) + 1) * (sizeof(char)));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, src, (ft_strlen(src) + 1));
	return (res);
}
