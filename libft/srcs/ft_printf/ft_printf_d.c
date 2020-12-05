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

static int	align_left_handle(int nbr, int l, t_info *info, char ch)
{
	if (nbr < 0)
		write(1, "-", 1);
	while (l < info->accuracy + (nbr < 0))
		l += write(1, "0", 1);
	if (nbr == -2147483648)
	{
		ft_putnbr(2);
		ft_putnbr(147483648);
	}
	else if (nbr < 0)
		ft_putnbr(-nbr);
	else
		ft_putnbr(nbr);
	while (l < info->width)
		l += write(1, &ch, 1);
	while (l < info->width - info->accuracy)
		l += write(1, &ch, 1);
	return (l);
}

static int	align_right_handle(int nbr, int l, t_info *info, char ch)
{
	int margin;

	if (info->flags == FILL_ZERO && nbr < 0)
		nbr = nbr * (-1) * write(1, "-", 1);
	margin = info->width - ft_max(info->accuracy, l) -
				(nbr < 0 && info->accuracy >= l);
	while (margin-- > 0)
		l += write(1, &ch, 1);
	if (nbr < 0 && nbr && info->flags != FILL_ZERO)
		write(1, "-", 1);
	margin = info->accuracy - (int)ft_nbrlen(nbr) + (nbr < 0);
	while (margin-- > 0)
		l += write(1, "0", 1);
	if (nbr == -2147483648)
	{
		ft_putnbr(2);
		ft_putnbr(147483648);
	}
	else if (nbr < 0)
		ft_putnbr(-nbr);
	else
		ft_putnbr(nbr);
	return (l);
}

int			ft_printf_d(int nbr, t_info *info)
{
	int		l;
	int		margin;
	char	ch;

	if (info->accuracy == 0 && nbr == 0)
	{
		margin = 0;
		while (margin < info->width)
			margin += write(1, " ", 1);
		return (margin);
	}
	if (info->accuracy == -1)
		info->accuracy = 0;
	else if (info->flags == FILL_ZERO)
		info->flags = 0;
	l = ft_nbrlen(nbr);
	ch = ' ';
	if (info->flags == FILL_ZERO)
		ch = '0';
	if (info->flags == ALIGN_LEFT)
		return (align_left_handle(nbr, l, info, ch));
	return (align_right_handle(nbr, l, info, ch));
}
