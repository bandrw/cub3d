/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:14:21 by kfriese           #+#    #+#             */
/*   Updated: 2020/11/19 11:14:23 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_printf_p(void *p, t_info *info)
{
	int		l;
	char	*arr;
	size_t	len;

	l = 0;
	if (!(arr = ft_hexstr((unsigned long)p)))
		return (-1);
	len = ft_strlen(arr);
	if (info->flags == ALIGN_LEFT)
	{
		l += ft_putstr("0x") + ft_putstr(arr);
		while (l < info->width)
			l += write(1, " ", 1);
	}
	else
	{
		while (len + 2 < (size_t)info->width)
			len += write(1, " ", 1);
		l += ft_putstr("0x") + ft_putstr(arr) + len - ft_strlen(arr);
	}
	free(arr);
	return (l);
}
