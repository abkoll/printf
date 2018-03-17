/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 06:02:56 by akoller           #+#    #+#             */
/*   Updated: 2018/03/12 06:03:13 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void			ft_putwidestring(t_print *f, wchar_t *str, int spaces)
{
	int			i;

	i = 0;
	while (f->minus == 0 && spaces-- > 0)
	{
		write(1, " ", 1);
		f->done++;
	}
	while (str[i])
	{
		if ((f->precision != -1) && ((i + 1) > f->precision))
			break ;
		write(1, &str[i++], 1);
		f->done++;
	}
	while (f->minus == 1 && spaces-- > 0)
	{
		write(1, " ", 1);
		f->done++;
	}
}

int				ft_widestrlen(const wchar_t *c)
{
	int			len;

	len = 0;
	while (c[len])
		len++;
	return (len);
}

int				ft_printwidestring(t_print *f, va_list *arg)
{
	wchar_t		*str;
	int			spaces;
	int			length;

	str = va_arg(*(arg), wchar_t *);
	if (!str)
		return (-1);
	length = ft_widestrlen(str);
	spaces = f->padding - length;
	if (f->precision < length && f->precision != -1)
		spaces = spaces - (f->precision - length);
	ft_putwidestring(f, str, spaces);
	return (1);
}

void			ft_printstring(t_print *f, va_list *arg)
{
	char		*str;
	int			spaces;
	int			length;

	str = va_arg(*(arg), char *);
	if (!str)
		str = "(null)";
	length = (int)ft_strlen(str);
	spaces = f->padding - length;
	if (f->precision < length && f->precision != -1)
		spaces = spaces - (f->precision - length);
	ft_putstring(f, str, spaces);
}

void			ft_putstring(t_print *f, char *str, int spaces)
{
	int			i;

	i = 0;
	while (f->minus == 0 && spaces-- > 0)
	{
		write(1, " ", 1);
		f->done++;
	}
	while (str[i])
	{
		if ((f->precision != -1) && ((i + 1) > f->precision))
			break ;
		write(1, &str[i++], 1);
		f->done++;
	}
	while (f->minus == 1 && spaces-- > 0)
	{
		write(1, " ", 1);
		f->done++;
	}
}
