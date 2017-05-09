/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:14:31 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/09 01:42:25 by kmurray          ###   ########.fr       */
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
		if (*lst == hold && ft_strcmp(hnode->fname, snode->fname) > 0)
		{
			*lst = hold->next;
			hold->next = scout->next;
			scout->next = hold;
		}
		else if (ft_strcmp(hnode->fname, snode->fname) > 0)
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

int main(int ac, char **av)
{
	int				len;
	DIR				*dirp;
	struct dirent	*dp;
	char			*name;
//	struct stat		test;
	t_list			*begin_list = NULL;
	t_file			*node;
	char			*str;
	t_list			*scout;
//	int				i = 0;

	if (ac == 2)
	{
		name = av[1];
		dirp = opendir(".");
		if (dirp == NULL)
		{
			ft_printf("ERROR\n");
			return (0);
		}
		len = ft_strlen(name);
		while ((dp = readdir(dirp)) != NULL)
		{
			node = ft_memalloc(sizeof(t_file));
			str = ft_strdup(str, dp->d_name);
			node->fname = str;
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
					ft_printf("%s\n", node->fname);
				scout = scout->next;
			}
		}
/*		ft_printf("%d\n", stat(name, &test));
		if (errno)
		{
			ft_printf("%d is ERRNO\n", errno);
			ft_printf("Oh dear, something went wrong with stat()! %s\n", strerror(errno));
		}
		else
		{
			ft_printf("Your eyes are so beautiful that you made no mistakes in the code this time! :%)\n");
			ft_printf("%o is the file mode\n", test.st_mode);
		}*/
	}
	return (0);
}
