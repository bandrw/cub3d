/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:31:33 by kfriese           #+#    #+#             */
/*   Updated: 2020/11/24 15:31:35 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	width_handle(const char *str, t_info *info, va_list *ap)
{
	int offset;

	offset = 0;
	if (*str == '*')
	{
		if (*(str + 1) == '\0')
			return (-1);
		info->width = va_arg(*ap, int);
		offset++;
	}
	else
	{
		while (*str == '0')
		{
			str++;
			offset++;
		}
		info->width = ft_atoi(str);
		if (info->width != 0)
			offset += (int)ft_nbrlen(info->width);
	}
	return (offset);
}

static int	accuracy_handle(const char *str, t_info *info, va_list *ap,
							int offset)
{
	if (*str == '.')
	{
		str++;
		offset++;
		if (*str == '*')
		{
			if (*(++str) == '\0')
				return (-1);
			info->accuracy = va_arg(*ap, int);
			offset++;
		}
		else
		{
			while (*str == '0')
			{
				str++;
				offset++;
			}
			info->accuracy = ft_atoi(str);
			if (info->accuracy != 0)
				offset += (int)ft_nbrlen(info->accuracy);
		}
	}
	return (offset);
}

static int	get_flags_width(const char *str, t_info *info, va_list *ap)
{
	int tmp;
	int offset;

	if ((offset = width_handle(str, info, ap)) == -1)
		return (-1);
	if (info->width < 0)
	{
		info->width = -info->width;
		info->flags = ALIGN_LEFT;
	}
	if ((tmp = accuracy_handle(str + offset, info, ap, 0)) == -1)
		return (-1);
	if (info->accuracy < 0)
		info->accuracy = -1;
	return (offset + tmp);
}

static int	flag_handle(const char **str, int *offset, t_info *info)
{
	if (**str == '0')
	{
		while (**str == '0')
		{
			(*str)++;
			(*offset)++;
		}
		if (**str == '\0')
			return (-1);
		if (info->flags != ALIGN_LEFT)
			info->flags = FILL_ZERO;
	}
	else if (**str == '-')
	{
		while (**str == '-')
		{
			(*str)++;
			(*offset)++;
		}
		if (**str == '\0')
			return (-1);
		info->flags = ALIGN_LEFT;
	}
	return (0);
}

int			get_flags(const char *str, t_info *info, va_list *ap)
{
	int tmp;
	int offset;

	offset = 0;
	info->width = 0;
	info->flags = 0;
	info->accuracy = -1;
	while (*str == '0' || *str == '-' || *str == ' ' ||
			*str == '#' || *str == '+')
	{
		if (flag_handle(&str, &offset, info) == -1)
			return (-1);
		if (*str == ' ' || *str == '#' || *str == '+')
		{
			str++;
			offset++;
		}
	}
	if ((tmp = get_flags_width(str, info, ap)) == -1)
		return (-1);
	return (offset + tmp);
}
