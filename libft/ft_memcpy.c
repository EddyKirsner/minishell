/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:01:04 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/04 12:10:00 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*original_dest;

	original_dest = dest;
	while (n > 0)
	{
		*((char *)dest) = *((char *)src);
		src++;
		dest++;
		n--;
	}
	return (original_dest);
}
