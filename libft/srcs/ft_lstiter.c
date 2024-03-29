/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:42:13 by kfriese           #+#    #+#             */
/*   Updated: 2020/10/31 17:42:15 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *, void *), void *data)
{
	if (!(lst && f))
		return ;
	while (lst)
	{
		(*f)(lst->content, data);
		lst = lst->next;
	}
}
