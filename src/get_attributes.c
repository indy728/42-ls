/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:51:40 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/15 23:06:25 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

size_t	get_attributes(t_file *file, char *path, t_options *options)
{
	struct stat		st;
	struct passwd	*pass;
	struct group	*grp;

	path = ft_strjoin(path, "/");
	path = ft_strmove(ft_strjoin(path, file->name), &path);
	if (lstat(path, &st) == -1)
	{
		perror("lstat error: ");
		exit (1);
	}
	file->mode = ft_strdup(check_permissions(st.st_mode));
	file->links = (unsigned int)st.st_nlink;
	if (!options->n && (pass = getpwuid(st.st_uid)))
		file->owner = ft_strdup(pass->pw_name);
	else
		file->owner = ft_itoa(st.st_uid);
	if (!options->n && (grp = getgrgid(st.st_gid)))
		file->group = ft_strdup(grp->gr_name);
	else
		file->group = ft_itoa(st.st_gid);
	file->size = (unsigned int)st.st_size;
	file->mod_time = st.st_mtime;
	free(path);
	return (st.st_blocks);
}
