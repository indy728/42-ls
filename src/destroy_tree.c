/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 23:57:07 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/16 22:39:49 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	destroy_tree(t_file *root)
{
	if (root)
	{
		destroy_tree(root->left);
		destroy_tree(root->right);
		free(root->name);
		free(root->mode);
		free(root->group);
		if (root->link)
			free(root->link);
		free(root);
	}
}
