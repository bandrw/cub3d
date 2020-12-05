/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:14:27 by kfriese           #+#    #+#             */
/*   Updated: 2020/11/19 11:14:28 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	left_align_handle(char *s, t_info *info, int l)
{
	int tmp;

	tmp = 0;
	while (tmp < info->accuracy && *(s + tmp) != '\0')
		tmp += write(1, s + tmp, 1);
	while (tmp < info->width)
	{
		l += write(1, " ", 1);
		tmp++;
	}
	return (l);
}

int			ft_printf_s(char *s, t_info *info)
{
	int l;
	int tmp;

	if (s == 0)
	{
		if (info->accuracy < 0)
			info->accuracy = -1;
		return (ft_printf_s("(null)", info));
	}
	l = ft_strlen(s);
	if (info->accuracy != -1 && info->accuracy < l)
		l = info->accuracy;
	if (info->accuracy == -1)
		info->accuracy = l;
	tmp = 0;
	if (info->flags == ALIGN_LEFT)
		return (left_align_handle(s, info, l));
	while (l < info->width)
		l += write(1, " ", 1);
	while (tmp < info->accuracy && *(s + tmp) != '\0')
		tmp += write(1, s + tmp, 1);
	return (l);
}
