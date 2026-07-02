/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:44:24 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/28 16:17:23 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "../libft.h"

int		ft_putchar_i(char c);
int		ft_putstr_i(char *s);
int		ft_putnbr_i(int n);
int		ft_putbase_i(unsigned long n, unsigned int base, int type);

int		ft_printf(const char *str, ...);

#endif
