/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:14:31 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/15 04:21:25 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_elem(t_file *file)
{
	ft_printf("name: %s\n"
			"mode: %s\n"
			"links: %u\n"
			"owner: %s\n"
			"group: %s\n"
			"left: %p\n"
			"right: %p\n", file->name, file->mode, file->links, file->owner,
			file->group, file->left, file->right);
}

static int	mark_options(int ac, char **av, t_options *options, int i)
{
	char	*str;
	int		j;

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
			else if (str[j] == 'S')
				options->big_s = 1;
		}
		++i;
		str = av[i];
	}
	return (i);
}

char check_type(mode_t mode)
{
	char	perm;

	perm = '-';
	if (S_ISDIR(mode))
		perm = 'd';
	else if (S_ISREG(mode))
		perm = '-';
	else if (S_ISLNK(mode))
		perm = 'l';
	else if (S_ISBLK(mode))
		perm = 'b';
	else if (S_ISCHR(mode))
		perm = 'c';
	else if (S_ISSOCK(mode))
		perm = 's';
	else if (S_ISFIFO(mode))
		perm = 'p';
	return (perm);
}

char *check_permissions(mode_t mode)
{
	char	*perm;

	perm = ft_strnew(10);
	perm = ft_memset(perm, '-', 10);
	perm[0] = check_type(mode);
	if (S_IRUSR & mode)
		perm[1] = 'r';
	if (S_IWUSR & mode)
		perm[2] = 'w';
	if (S_IXUSR & mode)
		perm[3] = 'x';
	if (S_IRGRP & mode)
		perm[4] = 'r';
	if (S_IWGRP & mode)
		perm[5] = 'w';
	if (S_IXGRP & mode)
		perm[6] = 'x';
	if (S_IROTH & mode)
		perm[7] = 'r';
	if (S_IWOTH & mode)
		perm[8] = 'w';
	if (S_IXOTH & mode)
		perm[9] = 'x';
	return (perm);
}

size_t	get_attributes(t_file *file, char *path)
{
	struct stat		st;
	char			*tmp;
	struct passwd	*pass;
	struct group	*grp;

	path = ft_strjoin(path, "/");
	tmp = ft_strjoin(path, file->name);
	if (lstat(tmp, &st) == -1)
	{
		ft_printf("lstat error\n");
		return (1);
	}
	file->mode = ft_strdup(check_permissions(st.st_mode));
	file->links = (unsigned int)st.st_nlink;
	if ((pass = getpwuid(st.st_uid)))
		file->owner = ft_strdup(pass->pw_name);
	else
		file->owner = ft_itoa(st.st_uid);
	if ((grp = getgrgid(st.st_gid)))
		file->group = ft_strdup(grp->gr_name);
	else
		file->group = ft_itoa(st.st_gid);
	file->size = (unsigned int)st.st_size;
	free(tmp);
	free(path);
	return (st.st_blocks);
}

int main(int ac, char **av)
{
	int				i;
	DIR				*dirp;
	struct dirent	*dp;
	char			*path;
	t_file			*tree_top = NULL;
	t_file			*node;
	t_options		options;

	ft_bzero(&options, sizeof(t_options));
	i = mark_options(ac, av, &options, 1);
	path = i < ac ? (av[i]) : (".");
	dirp = opendir(path);
	if (dirp == NULL)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		if(!(node = ft_memalloc(sizeof(t_file))))
			return (0);
		node->left = NULL;
		node->right = NULL;
		node->name = ft_strdup(dp->d_name);
		if (!options.a && node->name[0] == '.')
		{
			free(node);
			continue ;
		}
		get_attributes(node, path); 
		insert_elem(&tree_top, node, options);
	}
	(void)closedir(dirp);
	print_tree(tree_top, options);
	return (0);
}
