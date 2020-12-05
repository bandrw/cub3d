/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:01:30 by kfriese           #+#    #+#             */
/*   Updated: 2020/11/21 17:01:32 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_capitalize(char *str)
{
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'f')
			*str = *str + 'A' - 'a';
		str++;
	}
}

static int	ft_puthex(char *arr, t_info *info, int len, char ch)
{
	int l;
	int margin;

	l = 0;
	if (info->flags == ALIGN_LEFT)
	{
		while (l < info->accuracy - len)
			l += write(1, "0", 1);
		l += ft_putstr(arr);
		while (l < info->width)
			l += write(1, &ch, 1);
		return (l);
	}
	if (info->accuracy > len)
		margin = info->width - info->accuracy;
	else
		margin = info->width - len;
	while (l < margin)
		l += write(1, &ch, 1);
	margin = 0;
	while (margin < info->accuracy - len)
		margin += write(1, "0", 1);
	l += ft_putstr(arr) + margin;
	return (l);
}

int			ft_printf_x(unsigned int nbr, t_info *info, int upper)
{
	int		l;
	char	ch;
	char	*arr;

	if (!(arr = ft_hexstr((unsigned long)nbr)))
		return (0);
	if (nbr == 0 && info->accuracy == 0)
		*arr = '\0';
	if (upper)
		ft_capitalize(arr);
	ch = ' ';
	if (info->flags == FILL_ZERO && info->accuracy == -1)
		ch = '0';
	l = ft_puthex(arr, info, (int)ft_strlen(arr), ch);
	free(arr);
	return (l);
}
