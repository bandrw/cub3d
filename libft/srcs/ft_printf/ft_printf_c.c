/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:14:09 by kfriese           #+#    #+#             */
/*   Updated: 2020/11/19 11:14:10 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_c(unsigned char c, t_info *info)
{
	int		l;
	char	ch;

	l = 0;
	ch = ' ';
	if (info->flags == FILL_ZERO)
		ch = '0';
	if (info->flags == ALIGN_LEFT)
	{
		l += ft_putchar(c);
		while (l < info->width)
			l += write(1, &ch, 1);
	}
	else
	{
		while (l < info->width - 1)
			l += write(1, &ch, 1);
		l += ft_putchar(c);
	}
	return (l);
}
