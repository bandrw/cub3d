/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:07:54 by kfriese           #+#    #+#             */
/*   Updated: 2020/11/11 18:07:54 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define ALIGN_LEFT 1
# define FILL_ZERO 2

typedef struct		s_info
{
	int				width;
	int				accuracy;
	unsigned char	flags;
}					t_info;

int					ft_printf(const char *str, ...);
int					ft_printf_s(char *s, t_info *info);
int					ft_printf_d(int nbr, t_info *info);
int					ft_printf_c(unsigned char c, t_info *info);
int					ft_printf_p(void *p, t_info *info);
int					ft_printf_x(unsigned int nbr, t_info *info, int upper);
int					ft_printf_u(unsigned int nbr, t_info *info);
int					get_flags(const char *str, t_info *info, va_list *ap);

#endif
