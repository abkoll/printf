/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 06:17:40 by akoller           #+#    #+#             */
/*   Updated: 2018/03/07 06:17:45 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void			ft_printsignednum(t_print *f, intmax_t i)
{
	int			neg;
	uintmax_t	power;
	char		c;

	c = 0;
	neg = (i < 0) ? -1 : 1;
	power = ft_pow(f);
	power = power / f->base;
	while (i != 0 && power != 0)
	{
		c = (((i * neg) / power) + '0');
		write(1, &c, 1);
		f->done++;
		i = i - neg * ((i * neg) / power) * power;
		power = power / f->base;
	}
	while (i == 0 && power > 0)
	{
		if (f->precision != 0)
		{
			write(1, "0", 1);
			f->done++;
		}
		power = power / f->base;
	}
}

void			ft_prefix(t_print *f, intmax_t i)
{
	if (i < 0)
	{
		write(1, "-", 1);
		f->done++;
	}
	else if (f->plus == 1 && i >= 0)
	{
		write(1, "+", 1);
		f->done++;
	}
	else if (f->plus == 0 && f->space == 1 && i >= 0)
	{
		write(1, " ", 1);
		f->done++;
	}
}

intmax_t	ft_signedtypecast(t_print *f, intmax_t i)
{
	if ((f->len == PRINTF_L) || (f->caps == 1))
		return ((long int)i);
	if (f->len == PRINTF_NONE)
		return ((int)i);
	if (f->len == PRINTF_HH)
		return ((signed char)i);
	if (f->len == PRINTF_H)
	 	return ((short int)i);
	if (f->len == PRINTF_LL)
		return ((long long)i);
	if (f->len == PRINTF_Z)
	 	return ((size_t)i);
	else
		return (i);
}

// void			ft_printsignedmod(t_print *f, va_list *arg)
// {
// 	if ((f->len == PRINTF_L) || (f->caps == 1))
// 		f->uptr.l = va_arg(*(arg), intmax_t);
// 	else if (f->len == PRINTF_HH)
// 		f->uptr.c = va_arg(*(arg), intmax_t);
// 	else if (f->len == PRINTF_H)
// 		f->uptr.si = va_arg(*(arg), intmax_t);
// 	else if (f->len == PRINTF_LL)
// 		f->uptr.ll = va_arg(*(arg), intmax_t);
// 	else if (f->len == PRINTF_J)
// 		f->uptr.t = va_arg(*(arg), intmax_t);
// 	else if (f->len == PRINTF_Z)
// 		f->uptr.z = va_arg(*(arg), intmax_t);
// 	else
// 		f->uptr.i = va_arg(*(arg), intmax_t);
// 	ft_printsigned(f, f->uptr.t);
// }

void			ft_printsigned(t_print *f, va_list *arg)
{
	intmax_t	i;
	int			zeroes;
	int			spaces;

	spaces = 0;
	i = va_arg(*(arg), intmax_t);
	i = ft_signedtypecast(f, i);
	f->digits = ft_digits(f, i);
	zeroes = ft_signedzero(f, i);
	spaces = f->padding - f->digits - zeroes;
	if (i == 0 && f->precision == 0)
		spaces++;
	if (i < 0 || f->plus || f->space)
		spaces--;
	while (f->minus == 0 && spaces-- > 0)
	{
		write (1, " ", 1);
		f->done++;
	}
	ft_prefix(f, i);
	while (zeroes-- > 0)
	{
		write(1, "0", 1);
		f->done++;
	}
	ft_printsignednum(f, i);
	while (f->minus == 1 && (spaces-- > 0))
	{
		write(1, " ", 1);
		f->done++;
	}
}