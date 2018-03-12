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

uintmax_t		ft_unsignedtypecast(t_print *f, uintmax_t i)
{
	if (f->data == VAR_PTR)
		return (i);
	if ((f->len == PRINTF_L) || (f->data != VAR_HEX && f->caps == 1))
		return ((unsigned long int)i);
	if (f->len == PRINTF_NONE)
		return ((unsigned int)i);
	if (f->len == PRINTF_HH)
		return ((unsigned char)i);
	if (f->len == PRINTF_H)
		return ((unsigned short int)i);
	if (f->len == PRINTF_LL)
		return ((unsigned long long)i);
	if (f->len == PRINTF_Z)
		return ((size_t)i);
	else
		return (i);
}
