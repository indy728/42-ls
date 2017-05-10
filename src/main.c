/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:14:31 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/10 01:59:45 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*	int bufsize;
	char buffer[bufsize];
	struct passwd pwd, *result = NULL;

	if ((bufsize = sysconf(_SC_GETPW_R_SIZE_MAX)) == -1)
		abort();
	if (getpwuid_r(getuid(), &pwd, buffer, bufsize, &result) != 0 || !result)
		abort();
	ft_printf("%s\n", pwd.pw_dir);*/

void	sort_files(t_list **lst)
{
	t_list	*hold;
	t_list	*scout;
	t_list	*trail;
	t_file	*hnode;
	t_file	*snode;

	scout = *lst;
	while (scout->next)
	{
		hold = scout;
		hnode = hold->content;
		scout = scout->next;
		snode = scout->content;
		if (*lst == hold && ft_strcmp(hnode->name, snode->name) > 0)
		{
			*lst = hold->next;
			hold->next = scout->next;
			scout->next = hold;
		}
		else if (ft_strcmp(hnode->name, snode->name) > 0)
		{
			trail->next = hold->next;
			hold->next = scout->next;
			scout->next = hold;
			scout = *lst;
		}
		else
			trail = hold;
	}
}

static int	mark_options(int ac, char **av, t_options *options, int i)
{
	char	*str;
	int		j;

	if (ac == 1)
	{
	   return (0);
	   options = NULL;
	}
		

	str = av[i];
	while(i < ac && str[0] == '-')
	{
		j = 0;
		while (str[++j])
		{
			if (str[j] == 'l')
				options->l = 1;
			else if (str[j] == 'R')
				options->big_r = 1;
			else if (str[j] == 'a')
				options->a = 1;
			else if (str[j] == 'r')
				options->r = 1;
			else if (str[j] == 't')
				options->t = 1;
		}
		++i;
		str = av[i];
	}
	return (i);
}

int main(int ac, char **av)
{
	int				i;
	DIR				*dirp;
	struct dirent	*dp;
//	struct stat		test;
	t_list			*begin_list = NULL;
	t_file			*node;
	char			*str;
	t_list			*scout;
	t_options			options;

	if (ac == 1)
		return (0);
	ft_bzero(&options, sizeof(t_options));
	i = mark_options(ac, av, &options, 1);
	if (options.l)
		ft_putchar('l');
	if (options.big_r)
		ft_putchar('R');
	if (options.a)
		ft_putchar('a');
	if (options.r)
		ft_putchar('r');
	if (options.t)
		ft_putchar('t');
	ft_printf("\ni is %d\nthe next string is %s\n", i, av[i]);
	dirp = opendir(".");
	if (dirp == NULL)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		node = ft_memalloc(sizeof(t_file));
		str = ft_strdup(dp->d_name);
		node->name = str;
		ft_lstcat(&begin_list, ft_lstnew(node, sizeof(t_file)));
		free(node);
//			ft_printf("%s\n", dp->d_name);
/*		}
	}
	if (dp == NULL)
	{
		ft_printf("NOT_FOUND\n");
		(void)closedir(dirp);
	}*/
	}
	(void)closedir(dirp);
	if (begin_list)
	{
		sort_files(&begin_list);
		scout = begin_list;
		while (scout)
		{
			node = scout->content;
//				if (node->fname[0] != '.')
				ft_printf("%s\n", node->name);
			scout = scout->next;
		}
	}
	return (0);
}
