/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:50:50 by ktaouach          #+#    #+#             */
/*   Updated: 2024/05/22 13:19:37 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*original_dest;

	original_dest = dest;
	if (dest > src && (src + (n - 1)) >= dest)
	{
		dest += n - 1;
		src += n - 1;
		while (n > 0)
		{
			*((char *)dest) = *((char *)src);
			dest--;
			src--;
			n--;
		}
		return (original_dest);
	}
	while (n > 0 && src != dest)
	{
		*((char *)dest) = *((char *)src);
		src++;
		dest++;
		n--;
	}
	return (original_dest);
}
