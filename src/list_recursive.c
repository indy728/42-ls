/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_recursive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:03:11 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/15 23:22:45 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	list_recursive(char *path, t_file *root, t_options options)
{
	char	*tmp;

	if (root->left)
		list_recursive(path, root->left, options);
	if (root->mode[0] == 'd' && ft_strcmp(".", root->name) && ft_strcmp("..", root->name))
	{
		tmp = ft_strjoin(path, "/");
		tmp = ft_strjoin(tmp, root->name);
		ft_printf("\n%s:\n", tmp);
		build_tree(tmp, &options);
	}
	if (root->right)
		list_recursive(path, root->right, options);
}
