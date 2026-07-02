/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:27:43 by ktaouach          #+#    #+#             */
/*   Updated: 2024/05/22 13:23:42 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	count;
	void			*original_s;

	original_s = s;
	count = 1;
	while (count <= n)
	{
		*((char *)s) = c;
		count++;
		s++;
	}
	return (original_s);
}
