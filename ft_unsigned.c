/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 07:16:46 by akoller           #+#    #+#             */
/*   Updated: 2018/03/07 07:16:50 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int			ft_numlen_ull(uintmax_t value, unsigned int base)
{
	int		len;

	len = (value == 0) ? 1 : 0;
	while (value != 0)
	{
		value = value / base;
		len++;
	}
	return (len);
}

uintmax_t	ft_power_ull(uintmax_t nbr, uintmax_t power)
{
	uintmax_t tmp_nbr;

	tmp_nbr = nbr;
	if (power == 0)
		return (1);
	while (power-- > 1)
		nbr *= tmp_nbr;
	return (nbr);
}

// void			ft_upower(t_print *f, uintmax_t i);
// {
	
// }

void			ft_printunsignednum(t_print *f, uintmax_t i)
{
	char		c;
	uintmax_t	power;
	int			cap;

	c = 0;
	cap = (f->caps) ? '7' : 'W';
	// power = ft_pow(f) - 1;
	power = ft_power_ull(f->base, (ft_numlen_ull(i, f->base) - 1));
	// printf("%ju = power\n", power);
	// printf("%ju = i\n", i);
	while (i != 0 && power != 0)
	{
		if ((i / power) > 9)
		{
			c = ((i / power) + cap);
			write(1, &c, 1);
			f->done++;
		}
		else
		{
			c = (i / power) + '0';
			write(1, &c, 1);
			f->done++;
		}
		i = i - (i / power) * power;
		power = power / f->base;
	}
	while (i == 0 && power > 0)
	{
		if (f->precision != 0 || (f->hash == 1 && f->data == VAR_OCT))
		{
			write(1, "0", 1);
			f->done++;
		}
		power = power / f->base;
	}
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
		else if (f->hash == 1 && f->data == VAR_S)
			zeroes--;
	}
	return (zeroes);
}

void			ft_uprefix(t_print *f, uintmax_t i)
{
	if (f->data == VAR_PTR || (f->hash == 1 && i != 0))
	{
		if (f->data == VAR_OCT || f->data == VAR_HEX || f->data == VAR_PTR)
		{
			write(1, "0", 1);
			f->done++;
			if ((f->data == VAR_HEX && f->caps == 0) || f->data == VAR_PTR)
			{
				write(1, "x", 1);
				f->done++;
			}
			else if (f->data == VAR_HEX && f->caps == 1)
			{
				write(1, "X", 1);
				f->done++;
			}
		}
	}
}

uintmax_t	ft_unsignedtypecast(t_print *f, uintmax_t i)
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

// void			ft_printunsignedmod(t_print *f, va_list *arg)
// {
// 	if (f->data == VAR_PTR)
// 		f->uptr.ut = va_arg(*(arg), uintmax_t);
// 	if ((f->len == PRINTF_L) || (f->data != VAR_HEX && (f->caps == 1)))
// 		f->uptr.ul = va_arg(*(arg), uintmax_t);
// 	else if (f->len == PRINTF_HH)
// 		f->uptr.uc = va_arg(*(arg), uintmax_t);
// 	else if (f->len == PRINTF_H)
// 		f->uptr.us = va_arg(*(arg), uintmax_t);
// 	else if (f->len == PRINTF_LL)
// 		f->uptr.ull = va_arg(*(arg), uintmax_t);
// 	else if (f->len == PRINTF_J)
// 		f->uptr.ut = va_arg(*(arg), uintmax_t);
// 	else if (f->len == PRINTF_Z)
// 		f->uptr.z = va_arg(*(arg), uintmax_t);
// 	else
// 		f->uptr.i = va_arg(*(arg), uintmax_t);
// 	ft_printunsigned(f, f->uptr.ut);
// }

void			ft_printunsigned(t_print *f, va_list *arg)
{
	uintmax_t	i;
	int			zeroes;
	int			spaces;

	spaces = 0;
	i = va_arg(*(arg), uintmax_t);
	i = ft_unsignedtypecast(f, i);
	// i = u;
	f->udigits = ft_udigits(f, i);
	zeroes = ft_unsignedzero(f);
	spaces = f->padding - ft_numlen_ull(i, f->base) - zeroes;
	if (f->hash == 1 && f->data == VAR_OCT)
		zeroes--;
	if (i == 0 && f->precision == 0)
		spaces++;
	if (f->data == VAR_PTR || (f->hash == 1 && f->data == VAR_HEX))
		spaces-= 2;
	else if (f->hash == 1 && f->data == VAR_OCT)
		spaces--;
	while (f->minus == 0 && spaces-- > 0)
	{
		write (1, " ", 1);
		f->done++;
	}
	ft_uprefix(f, i);
	// printf("test3\n");
	while (zeroes-- > 0)
	{
		write(1, "0", 1);
		f->done++;
	}
	ft_printunsignednum(f, i);
	while (f->minus == 1 && (spaces-- > 0))
	{
		write(1, " ", 1);
		f->done++;
	}
}