/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:34:58 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/15 23:23:08 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	build_tree(char *path, t_options *options)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_file			*node;
	t_file			*tree_top;
	size_t			blocks = 0;

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
	{
		while ((dp = readdir(dirp)))
		{
			if (!(node = ft_memalloc(sizeof(t_file))))
			{
				perror("Error: ");
				exit (1);
			}
			ft_bzero(node, sizeof(t_file));
			node->name = ft_strdup(dp->d_name);
			if ((options->big_a && (!ft_strcmp(".", node->name) ||
				!ft_strcmp("..", node->name))) ||
				(!options->a && !options->big_a && node->name[0] == '.'))
			{
				free(node);
				continue ;
			}
			blocks += get_attributes(node, path, options);
			insert_elem(&tree_top, node, *options);
		}
		(void)closedir(dirp);
		if (options->l)
			ft_printf("total %lu\n", blocks);
		print_tree(tree_top, *options);
		if (options->big_r)
			list_recursive(path, tree_top, *options);
	}
}
