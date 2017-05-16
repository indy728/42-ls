/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 21:42:27 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/15 23:09:49 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	insert_params(t_params **root, t_params *node)
{
	if (!*root)
		*root = node;
	else
	{
		if (ft_strcmp((*root)->param, node->param) >= 0)
			insert_params(&(*root)->left, node);
		else
			insert_params(&(*root)->right, node);
	}
}

static void alpha_params(t_params *params, t_options *options)
{
	if (params->left)
		alpha_params(params->left, options);
	build_tree(params->param, options);
	if (params->right)
		alpha_params(params->right, options);
}

static void	destroy_ptree(t_params *params)
{
	if (params)
	{
		destroy_ptree(params->left);
		destroy_ptree(params->right);
		free(params);
	}
}

void		param_tree(int ac, char **av, int i, t_options *options)
{
	t_params	*params;
	t_params	*node;

	params = NULL;
	while (i < ac)
	{
		if(!(node = ft_memalloc(sizeof(t_params))))
		{
			perror("Error: ");
			exit (1);
		}
		ft_bzero(node, sizeof(t_params));
		node->param = ft_strdup(av[i]);
		insert_params(&params, node);
		++i;
	}
	alpha_params(params, options);
	destroy_ptree(params);
}
