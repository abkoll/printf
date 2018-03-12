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

void			ft_digits(t_print *f, intmax_t i)
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
	dig = f->digits;
	while (dig-- > 1)
		power *= f->base;
	power /= f->base;
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

void			ft_printchar(t_print *f, va_list *arg)
{
	char		c;
	char		prec;

	prec = (f->data == VAR_INVSPC && f->zero == 1) ? '0' : ' ';
	if (f->data == VAR_C)
		c = va_arg(*(arg), int);
	else
		c = f->invalidspec;
	if (f->minus)
	{
		write(1, &c, 1);
		f->done++;
	}
	while (f->padding-- > 1)
	{
		write(1, &prec, 1);
		f->done++;
	}
	if (f->minus == 0)
	{
		write(1, &c, 1);
		f->done++;
	}
}
