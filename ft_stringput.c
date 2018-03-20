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
	if (!(f->minus))
		ft_spaceput(f, spaces);
	while (str[i])
	{
		if ((f->precision != -1) && ((i + 1) > f->precision))
			break ;
		write(1, &str[i++], 1);
		f->done++;
	}
	if (f->minus)
		ft_spaceput(f, spaces);
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
	if (!(f->minus))
		ft_spaceput(f, spaces);
	length = 0;
	while (str[length])
	{
		if ((f->precision != -1) && ((length) > f->precision - 1))
			break ;
		length++;
	}
	write(1, str, length);
	f->done += length;
	if (f->minus)
		ft_spaceput(f, spaces);
}
