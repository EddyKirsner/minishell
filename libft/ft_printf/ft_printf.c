/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:48:27 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/10 17:18:37 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static
	int	check_ptr(size_t ptr)
{
	int	len;

	len = 0;
	if (!ptr)
		return (ft_putstr_i("(nil)"));
	len += ft_putstr_i("0x");
	len += ft_putbase_i(ptr, 16, 0);
	return (len);
}

static
	int	treatment(va_list arg, char c)
{
	int	len;

	if (c == 'c')
		len = ft_putchar_i((char)va_arg(arg, int));
	if (c == 's')
		len = ft_putstr_i((char *)va_arg(arg, char *));
	if (c == 'p')
		len = check_ptr((size_t)va_arg(arg, void *));
	if (c == 'd' || c == 'i')
		len = ft_putnbr_i((int)va_arg(arg, int));
	if (c == 'u')
		len = ft_putbase_i((unsigned int)va_arg(arg, unsigned int), 10, 0);
	if (c == 'x')
		len = ft_putbase_i((unsigned int)va_arg(arg, int), 16, 0);
	if (c == 'X')
		len = ft_putbase_i((unsigned int)va_arg(arg, int), 16, 1);
	return (len);
}

static
	int	handle(char c, va_list args, int *total)
{
	int	len;

	if (!ft_strchr("cspdiuxX%", c))
		return (-1);
	if (c == '%')
		len = ft_putchar_i('%');
	else
		len = treatment(args, c);
	if (len < 0)
		return (-1);
	*total += len;
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	size_t	i;
	va_list	args;

	if (!str)
		return (-1);
	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (handle(str[i + 1], args, &len) < 0)
				return (-1);
			i++;
		}
		else
			len += ft_putchar_i(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}
