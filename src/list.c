/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 01:13:23 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/09 01:18:49 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int list_read(t_posib *option, char **path, t_data **data, int i)
{
	int		nb;
	char	*bpath;

	if (option->rec && i > 0) //option->nb_path > 1
	{
		ft_putstr(*path);
		ft_putendl(":");
	}
	bpath = ft_strjoin(*path, "/"); //./ need to free!!
	ft_printf("bpath: %s\n", bpath);
	nb = 0;
	if ((*data = read_directories(bpath, *path, option, &nb)) == NULL)
		return (0);
	ft_strdel(&bpath);
	return (1);
}


int  list_recursive(t_posib *option, char *path, int i)
{
	t_data *data = NULL;
	t_data *elem;

	//  just reading the list without sorting or doing any recursive
	//SEcond part will take care of recursive big R
	if (list_read(option, &path, &data, i) == 0)
	{
		//printf("Error reading the list\n");
		return (0);
	}
	elem = data;
	/*
	do recursive if R is find as much as i != 0
	elem = elem->next to goo through each directori and list

	*/
	// while (elem && option->rec)
	// {
	//   list_bigr(option, elem, path, i);
	//   elem = elem->next;
	// }
	//make a function to free everything
	return(0);
}

void	list(t_posib *option)
{
	int		i;
	t_data	*data;
	char	*tmp = NULL;

	data = NULL;
	ft_printf("option->nb_path: %d\n", option->nb_path);
	i = 0;
	while (i < option->nb_path)
	{
		if (option->path[i] != NULL)
		{
			tmp = ft_strdup(option->path[i]);
			printf("tmp(list): %s\n", tmp);
			list_recursive(option, tmp, i);
			free(tmp);
		}
		i++;
	}
}
