/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfriese <kfriese@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:35:48 by kfriese           #+#    #+#             */
/*   Updated: 2020/11/03 16:35:49 by kfriese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		tmp_lstadd_back(t_list **lst, void *data)
{
	t_list *list;
	t_list *new;

	new = 0;
	if (!data || !(new = (t_list*)malloc(sizeof(t_list))))
	{
		ft_lstclear(lst, free);
		if (new)
			free(new);
		return (-1);
	}
	new->content = data;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		list = *lst;
		while (list->next)
			list = list->next;
		list->next = new;
	}
	return (0);
}

static size_t	get_list_len(t_list *list)
{
	size_t l;

	l = 0;
	while (list)
	{
		l += ft_strlen((char*)list->content);
		list = list->next;
	}
	return (l);
}

static int		final_string(t_list **list, char **line)
{
	char	*tmp;
	t_list	*list_tmp;
	size_t	len;

	if (!*list)
		tmp_lstadd_back(list, ft_strdup(""));
	if (!(line &&
		(*line = (char*)malloc(sizeof(char) * (get_list_len(*list) + 1)))))
	{
		ft_lstclear(list, free);
		return (-1);
	}
	tmp = *line;
	list_tmp = *list;
	while (list_tmp)
	{
		len = ft_strlen((char*)list_tmp->content);
		ft_strlcpy(tmp, (char*)list_tmp->content, len + 1);
		tmp += len;
		list_tmp = list_tmp->next;
	}
	ft_lstclear(list, free);
	return (1);
}

int				new_line_handle(char **new_line_p, t_list **list, char **line)
{
	char	*ptr;
	size_t	len;

	if (*new_line_p)
	{
		ptr = ft_strchr(*new_line_p + 1, '\n');
		if (ptr)
			len = ptr - (*new_line_p + 1);
		else
			len = ft_strlen(*new_line_p + 1);
		if (tmp_lstadd_back(list, ft_substr(*new_line_p + 1, 0, len)) == -1)
			return (0);
		if ((*new_line_p = ft_strchr(*new_line_p + 1, '\n')))
		{
			if (final_string(list, line) == 1)
				return (1);
			*new_line_p = 0;
			return (1);
		}
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int			bytes_read;
	size_t		len;
	t_list		*list;
	static char	*new_line_p;
	static char	str[BUFFER_SIZE + 1];

	list = 0;
	if (new_line_handle(&new_line_p, &list, line) == 1)
		return (1);
	while ((bytes_read = read(fd, str, BUFFER_SIZE)) > 0)
	{
		str[bytes_read] = '\0';
		if ((new_line_p = ft_strchr(str, '\n')))
		{
			len = new_line_p ? new_line_p - str : ft_strlen(str);
			if (tmp_lstadd_back(&list, ft_substr(str, 0, len)) == -1)
				return (-1);
			return (final_string(&list, line));
		}
		if (tmp_lstadd_back(&list, ft_strdup("")) == -1)
			return (-1);
	}
	if (final_string(&list, line) == 1)
		return (bytes_read);
	return (-1);
}
