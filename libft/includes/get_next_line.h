/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:37:54 by kfriese           #+#    #+#             */
/*   Updated: 2020/11/03 16:37:55 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 4096

# endif

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);

#endif
