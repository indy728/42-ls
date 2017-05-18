/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:51:40 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/17 22:23:16 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static char	*get_link(char *path)
{
	char	*link;
	int		ret;
	char	buf[1024];

	if ((ret = readlink(path, buf, 1024)) == -1)
	{
		perror("readlink error");
		exit(1);
	}
	buf[ret] = '\0';
	link = ft_strdup(buf);
	return (link);
}

static void	get_time(t_file *file, struct stat st, t_options *options)
{
	if (options->c)
	{
		file->time = st.st_ctime;
		file->ntime = st.st_ctimespec.tv_nsec;
	}
	else if (options->u)
	{
		file->time = st.st_atime;
		file->ntime = st.st_atimespec.tv_nsec;
	}
	else
	{
		file->time = st.st_mtime;
		file->ntime = st.st_mtimespec.tv_nsec;
	}
}

size_t		get_attributes(t_file *file, char *path, t_options *options)
{
	struct stat		st;
	struct passwd	*pass;
	struct group	*grp;

	path = ft_strjoin(path, "/");
	path = ft_strmove(ft_strjoin(path, file->name), &path);
	if (lstat(path, &st) == -1)
	{
		perror("lstat error");
		exit(1);
	}
	file->mode = ft_strdup(check_permissions(st.st_mode));
	file->nlink = (unsigned int)st.st_nlink;
	if (!options->n && (pass = getpwuid(st.st_uid)))
		file->owner = ft_strdup(pass->pw_name);
	else
		file->owner = ft_itoa(st.st_uid);
	if (!options->n && (grp = getgrgid(st.st_gid)))
		file->group = ft_strdup(grp->gr_name);
	else
		file->group = ft_itoa(st.st_gid);
	get_time(file, st, options);
	file->size = (unsigned int)st.st_size;
	if (file->mode[0] == 'l')
		file->link = get_link(path);
	free(path);
	return (st.st_blocks);
}
