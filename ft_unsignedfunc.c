/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsignedfunc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 06:09:05 by akoller           #+#    #+#             */
/*   Updated: 2018/03/12 06:09:26 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

uintmax_t		ft_upow(t_print *f)
{
	uintmax_t	power;
	uintmax_t	udig;

	udig = f->udigits - 1;
	power = f->base;
	if (udig == 0)
		return (1);
	while (udig-- > 1)
		power *= f->base;
	return (power);
}

int				ft_unsignedzero(t_print *f)
{
	int			zeroes;
	uintmax_t	dig;

	zeroes = 0;
	dig = f->udigits;
	if (f->precision >= (int)dig)
		zeroes = f->precision - dig;
	else if ((f->zero && f->padding > 0) && f->minus == 0)
	{
		zeroes = f->padding - dig;
		if (f->data == VAR_PTR || (f->hash == 1 && f->data == VAR_HEX))
			zeroes -= 2;
	}
	return (zeroes);
}

uintmax_t		ft_udigits(t_print *f, uintmax_t i)
{
	uintmax_t	digits;

	if (i == 0)
		return (1);
	digits = 0;
	while (i != 0)
	{
		i = i / f->base;
		digits++;
	}
	return (digits);
}

void			ft_printunsignedmod(t_print *f, va_list *arg)
{
	f->uptr.z = 0;
	if (f->data == VAR_PTR)
		f->uptr.ut = va_arg(*(arg), uintmax_t);
	else if ((f->len == PRINTF_L) || (f->data != VAR_HEX && (f->caps == 1)))
		f->uptr.ul = va_arg(*(arg), uintmax_t);
	else if (f->len == PRINTF_HH)
		f->uptr.uc = va_arg(*(arg), uintmax_t);
	else if (f->len == PRINTF_H)
		f->uptr.us = va_arg(*(arg), uintmax_t);
	else if (f->len == PRINTF_LL)
		f->uptr.ull = va_arg(*(arg), uintmax_t);
	else if (f->len == PRINTF_J)
		f->uptr.ut = va_arg(*(arg), uintmax_t);
	else if (f->len == PRINTF_Z)
		f->uptr.z = va_arg(*(arg), uintmax_t);
	else
		f->uptr.ui = va_arg(*(arg), uintmax_t);
	ft_printunsigned(f, f->uptr.ut);
}
