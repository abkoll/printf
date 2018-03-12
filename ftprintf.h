/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:05:57 by akoller           #+#    #+#             */
/*   Updated: 2018/02/26 12:06:02 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_H
# define FTPRINTF_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <wchar.h>
# include <limits.h>
# include <stdbool.h>

typedef union
{
	size_t				z;
	intmax_t			t;
	uintmax_t			ut;
	unsigned long long	ull;
	long long			ll;
	unsigned long		ul;
	long				l;
	double				d;
	int					i;
	unsigned int		ui;
	short				si;
	unsigned short		us;
	unsigned char		uc;
	char				c;
	void				*v;
} 						u_print;

enum 				e_pfvar
{
	VAR_C,
	VAR_I,
	VAR_S,
	VAR_OCT,
	VAR_HEX,
	VAR_UI,
	VAR_PTR,
	VAR_INVSPC
};

enum				e_printflag
{
	PRINTF_NONE,
	PRINTF_HH,
	PRINTF_H,
	PRINTF_L,
	PRINTF_LL,
	PRINTF_J,
	PRINTF_Z
}; 

typedef struct 		s_print
{
	unsigned int	done;
	int				index;
	int				base;
	int				data;
	int				invalidspec;
	bool			minus;
	bool			plus;
	bool			space;
	bool			hash;
	bool			zero;
	bool			caps;
	int				padding;
	int				precision;
	int				len;
	intmax_t		digits;
	uintmax_t		udigits;
	u_print			uptr;
}					t_print;

int					ft_printf(const char* format, ...);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
void				ft_parser(const char *format, t_print *f);
void				ft_escapeparser(const char *format, t_print *f);
void				ft_varcheck(const char *fm, t_print *f);
void				ft_printstring(t_print *f, va_list *arg);
void				ft_printchar(t_print *f, va_list *arg);
void				ft_printsigned(t_print *f, va_list *arg);
void				ft_printunsignedmod(t_print *f, va_list *arg);
void				ft_printunsigned(t_print *f, uintmax_t u);
size_t				ft_strlen(const char *s);
uintmax_t			ft_pow(t_print *f);
void				ft_putstr(t_print *f, char *str, int spaces);
int					ft_signedzero(t_print *f, intmax_t i);
intmax_t			ft_digits(t_print *f, intmax_t i);
void				ft_write(t_print *f, char c);
void				ft_printsignedmod(t_print *f, va_list *arg);

#endif