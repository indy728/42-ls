/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:34:58 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/16 17:24:38 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_file	*get_node(t_file *node, struct dirent *dp, t_options *options)
{
	if (!(node = ft_memalloc(sizeof(t_file))))
	{
		perror("Error: ");
		exit(1);
	}
	ft_bzero(node, sizeof(t_file));
	node->name = ft_strdup(dp->d_name);
	if ((options->big_a && (!ft_strcmp(".", node->name) ||
		!ft_strcmp("..", node->name))) ||
		(!options->a && !options->big_a && node->name[0] == '.'))
	{
		free(node->name);
		free(node);
		node = NULL;
	}
	return (node);
}

static void		populate_tree(DIR *dirp, t_file *tree_top,
											char *path, t_options *options)
{
	struct dirent	*dp;
	t_file			*node;
	unsigned int	blocks;

	blocks = 0;
	while ((dp = readdir(dirp)))
	{
		if (!(node = get_node(node, dp, options)))
			continue ;
		blocks += get_attributes(node, path, options);
		insert_elem(&tree_top, node, *options);
	}
	(void)closedir(dirp);
	if (options->l)
		ft_printf("total %u\n", blocks);
	print_tree(tree_top, *options);
	if (options->big_r)
		list_recursive(path, tree_top, *options);
	destroy_tree(tree_top);
}

void			build_tree(char *path, t_options *options)
{
	DIR				*dirp;
	t_file			*tree_top;

	tree_top = NULL;
	dirp = opendir(path);
	if (dirp == NULL)
	{
		if (errno == 20)
			ft_printf("%s\n", path);
		else
			ft_printf("ft_ls: %s: %s\n", path, strerror(errno));
		errno = 0;
	}
	else
		populate_tree(dirp, tree_top, path, options);
}
