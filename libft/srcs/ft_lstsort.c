/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 07:08:55 by kfriese           #+#    #+#             */
/*   Updated: 2021/02/07 07:08:57 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **begin_list, int (*cmp)())
{
	t_list	*list_i;
	t_list	*list_j;
	void	*tmp;

	if (!(begin_list && cmp))
		return ;
	list_i = *begin_list;
	while (list_i)
	{
		list_j = list_i->next;
		while (list_j)
		{
			if ((*cmp)(list_i->content, list_j->content) > 0)
			{
				tmp = list_i->content;
				list_i->content = list_j->content;
				list_j->content = tmp;
			}
			list_j = list_j->next;
		}
		list_i = list_i->next;
	}
}
