/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:14:14 by kfriese           #+#    #+#             */
/*   Updated: 2020/11/19 11:14:16 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_putunbr(unsigned int n)
{
	if (n > 9)
	{
		ft_putunbr(n / 10);
		ft_putunbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

static size_t	ft_nbrulen(unsigned int nbr)
{
	size_t l;

	l = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		l++;
		nbr = nbr / 10;
	}
	return (l);
}

static int		align_right_handle(t_info *info, char ch,
									unsigned int nbr, int l)
{
	int tmp;

	if (l >= info->accuracy)
	{
		while (l < info->width)
			l += write(1, &ch, 1);
		ft_putunbr(nbr);
	}
	else
	{
		tmp = 0;
		while (tmp < info->width - info->accuracy)
			tmp += write(1, &ch, 1);
		while (l < info->accuracy)
			l += write(1, "0", 1);
		l += tmp;
		ft_putunbr(nbr);
	}
	return (l);
}

static int		align_left_handle(int l, t_info *info, char ch,
									unsigned int nbr)
{
	while (l < info->accuracy)
		l += write(1, "0", 1);
	ft_putunbr(nbr);
	while (l < info->width)
		l += write(1, &ch, 1);
	return (l);
}

int				ft_printf_u(unsigned int nbr, t_info *info)
{
	int		l;
	char	ch;

	if (nbr == 0 && info->accuracy == 0)
	{
		l = 0;
		while (l < info->width)
			l += write(1, " ", 1);
		return (l);
	}
	l = ft_nbrulen(nbr);
	ch = ' ';
	if (info->flags == FILL_ZERO && info->accuracy == -1)
		ch = '0';
	if (info->flags == ALIGN_LEFT)
		return (align_left_handle(l, info, ch, nbr));
	return (align_right_handle(info, ch, nbr, l));
}
