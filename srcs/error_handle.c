/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:13:34 by kfriese           #+#    #+#             */
/*   Updated: 2021/01/07 12:13:35 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		usage_error(char *program_name)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(program_name, 2);
	ft_putstr_fd(" map.cub\n", 2);
	exit(1);
}

void	simple_error(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	exit(1);
}
