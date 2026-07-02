/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:31:51 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/28 15:43:41 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_i(char c)
{
	int	len;

	len = write(1, &c, 1);
	if (len < 0)
		return (-5000);
	return (len);
}

int	ft_putstr_i(char *s)
{
	unsigned int	siz;

	if (!s)
		return (write(1, "(null)", 6));
	siz = ft_strlen(s);
	return (write(1, s, siz));
}

int	ft_putnbr_i(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = -147483648;
			len += ft_putstr_i("-2");
		}
		else
			len += ft_putchar_i('-');
		n *= -1;
		if (len < 0)
			return (-1);
	}
	if (n >= 10)
		len += ft_putnbr_i(n / 10);
	len += ft_putchar_i((n % 10) + 48);
	return (len);
}

int	ft_putbase_i(unsigned long n, unsigned int base, int type)
{
	char	*hex;
	char	*hex2;
	char	*dig;
	int		len;

	len = 0;
	hex = "0123456789abcdef";
	hex2 = "0123456789ABCDEF";
	dig = "0123456789";
	if (n >= base)
		len += ft_putbase_i(n / base, base, type);
	if (base == 16 && !type)
		len += ft_putchar_i(hex[n % base]);
	if (base == 16 && type)
		len += ft_putchar_i(hex2[n % base]);
	if (base == 10)
		len += ft_putchar_i(dig[n % base]);
	return (len);
}
