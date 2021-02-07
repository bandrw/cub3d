/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 07:09:12 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/07 07:09:14 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstmerge(t_list **begin_list1, t_list *begin_list2)
{
	t_list *list;

	if (begin_list1 && begin_list2)
	{
		list = *begin_list1;
		if (list)
		{
			while (list->next)
				list = list->next;
			list->next = begin_list2;
		}
		else
			*begin_list1 = begin_list2;
	}
}
