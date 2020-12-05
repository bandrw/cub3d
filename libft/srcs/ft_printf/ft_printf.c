/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:29:03 by kfriese           #+#    #+#             */
/*   Updated: 2020/11/11 17:29:04 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	apply_flags(const char *str, t_info *info, va_list *ap)
{
	if (ft_tolower(*(str + 1)) == 's')
		return (ft_printf_s(va_arg(*ap, char *), info));
	else if (ft_tolower(*(str + 1)) == 'd' || ft_tolower(*(str + 1)) == 'i')
		return (ft_printf_d(va_arg(*ap, int), info));
	else if (ft_tolower(*(str + 1)) == 'u')
		return (ft_printf_u(va_arg(*ap, unsigned int), info));
	else if (ft_tolower(*(str + 1)) == 'c')
		return (ft_printf_c(va_arg(*ap, int), info));
	else if (ft_tolower(*(str + 1)) == '%')
		return (ft_printf_c('%', info));
	else if (ft_tolower(*(str + 1)) == 'p')
		return (ft_printf_p(va_arg(*ap, void *), info));
	else if (ft_tolower(*(str + 1)) == 'x')
		return (ft_printf_x(va_arg(*ap, unsigned long), info, str[1] == 'X'));
	return (-1);
}

static int	format_handle(const char *str, t_info *info, va_list *ap)
{
	int total;
	int offset;
	int flags_length;

	total = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			if (*(str + 1) == '\0')
				return (total);
			if ((flags_length = get_flags(str + 1, info, ap)) == -1)
				return (total);
			if ((offset = apply_flags(str + flags_length, info, ap)) == -1)
				return (total);
			total += offset;
			str += flags_length + 1;
		}
		else
			total += write(1, str, 1);
		str++;
	}
	return (total);
}

int			ft_printf(const char *str, ...)
{
	int		total;
	t_info	*info;
	va_list	ap;

	if (!str || !(info = (t_info*)malloc(sizeof(t_info))))
		return (0);
	va_start(ap, str);
	total = format_handle(str, info, &ap);
	va_end(ap);
	free(info);
	return (total);
}
