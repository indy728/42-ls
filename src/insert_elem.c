/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 03:07:02 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/16 00:21:38 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	insert_elem(t_file **tree_top, t_file *new_leaf, t_options options)
{
	int		value;

	if (*tree_top == NULL)
		*tree_top = new_leaf;
	else
	{
		if (options.big_s)
			value = new_leaf->size - (*tree_top)->size;
		else if (options.t)
			value = new_leaf->mod_time - (*tree_top)->mod_time;
		else
			value = ft_strcmp((*tree_top)->name, new_leaf->name);
		value = options.r ? value *= -1 : value;
		if (value > 0)
			insert_elem(&(*tree_top)->left, new_leaf, options);
		else
			insert_elem(&(*tree_top)->right, new_leaf, options);
	}
}
