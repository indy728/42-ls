/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 02:57:09 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/15 04:14:18 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_tree(t_file *file, t_options options)
{
	if (file)
	{
		if (file->left)
			print_tree(file->left, options);
		if (options.l)
			ft_printf("%10s  %u %s  %s  %d  %s\n", file->mode, file->links,
					file->owner, file->group, file->size, file->name);
		else
			ft_printf("%-11s\n", file->name);
		if (file->right)
			print_tree(file->right, options);
	}
}
