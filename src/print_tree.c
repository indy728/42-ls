/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 02:57:09 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/16 17:24:44 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static char	*read_date(char *ctime, char *date)
{
	date = ft_strncat(date, ctime + 4, 12);
	date[12] = '\0';
	return (date);
}

static void	print_recursive(t_file *file, t_options options)
{
	char		*date;

	if (file)
	{
		if (file->left)
			print_recursive(file->left, options);
		if (options.l)
		{
			date = ft_strnew(13);
			ft_printf("%10s %3u %8s %10s %6d %s %s\n", file->mode, file->links,
					file->owner, file->group, file->size,
					read_date(ctime(&file->mod_time), date), file->name);
			free(date);
		}
		else
			ft_printf("%s\n", file->name);
		if (file->right)
			print_recursive(file->right, options);
	}
}

void		print_tree(t_file *file, t_options options)
{
	print_recursive(file, options);
}
