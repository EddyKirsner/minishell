/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:35:46 by ktaouach          #+#    #+#             */
/*   Updated: 2025/03/26 15:40:35 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if ((unsigned char) s1[i] == (unsigned char) s2[i])
			i++;
		else
			break ;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
