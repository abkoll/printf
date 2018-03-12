/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:06:46 by akoller           #+#    #+#             */
/*   Updated: 2018/03/06 16:06:48 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void		ft_digits(t_print *f, intmax_t i)
{
	intmax_t	digits;

	if (i == 0)
		digits = 1;
	else
		digits = 0;
	while (i != 0)
	{
		i = i / f->base;
		digits++;
	}
	f->digits = digits;
}

uintmax_t		ft_pow(t_print *f)
{
	intmax_t	dig;
	uintmax_t	power;

	power = f->base;
	dig	= f->digits;
	while (dig-- > 1)
		power *= f->base;
	return (power);
}

int				ft_signedzero(t_print *f, intmax_t i)
{
	int			zeroes;
	intmax_t	dig;

	zeroes = 0;
	dig = f->digits;
	if (f->precision >= dig)
		zeroes = f->precision - dig;
	else if (f->zero == 1 && f->padding > 0 && f->minus == 0)
	{
		zeroes = f->padding - dig;
		if (i < 0 || f->plus || f->space)
			zeroes--;
	}
	return (zeroes);
}

// void		ft_strcast(t_print *f, va_list *arg)
// {
// 	if (f->caps == 1)
// 		f->uptr.wc = *(va_arg(*(arg), wchar_t *));
// 	else
// 		f->uptr.c = *(va_arg(*(arg), char *));
// 	ft_printstring(f, &f->uptr.wc);
// }

void	ft_putwidestring(t_print *f, wchar_t *str, int spaces)
{
	int		i;

	i = 0;
	while (f->minus == 0 && spaces-- > 0)
	{
		write(1, " ", 1);
		f->done++;
	}
	while (str[i])
	{
		if((f->precision != -1) && ((i + 1) > f->precision))
			break;
		write(1, &str[i++], 1);
		f->done++;
	}
	while (f->minus == 1 && spaces-- > 0)
	{
		write(1, " ", 1);
		f->done++;
	}
}

int			ft_widestrlen(const wchar_t *c)
{
	int		len;
	len = 0;
	while (c[len])
		len++;
	return (len);
}

void		ft_printwidestring(t_print *f, va_list *arg)
{
	wchar_t		*str;
	int			spaces;
	int			length;

	str = va_arg(*(arg), wchar_t *);
	length = ft_widestrlen(str);
	spaces = f->padding - length;
	if (f->precision < length && f->precision != -1)
		spaces = spaces - (f->precision - length);
	ft_putwidestring(f, str, spaces);
}

void		ft_printstring(t_print *f, va_list *arg)
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

void	ft_putstring(t_print *f, char *str, int spaces)
{
	int		i;

	i = 0;
	while (f->minus == 0 && spaces-- > 0)
	{
		write(1, " ", 1);
		f->done++;
	}
	while (str[i])
	{
		if((f->precision != -1) && ((i + 1) > f->precision))
			break;
		write(1, &str[i++], 1);
		f->done++;
	}
	while (f->minus == 1 && spaces-- > 0)
	{
		write(1, " ", 1);
		f->done++;
	}
}

void	ft_printchar(t_print *f, va_list *arg)
{
	char	c;
	char	prec;

	if (f->data == VAR_INVSPC && f->zero == 1)
		prec = '0';
	else (prec = ' ');
	if (f->data == VAR_C)
		c = va_arg(*(arg), int);
	else
		c = f->invalidspec;
	if (f->minus)
	{
		write(1, &c, 1);
		f->done++;
	}
	while (f->padding > 1)
	{
		write(1, &prec, 1);
		f->done++;
		f->padding--;
	}
	if (f->minus == 0)
	{
		write(1, &c, 1);
		f->done++;
	}
}