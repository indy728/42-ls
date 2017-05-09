/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 18:29:02 by alcornea          #+#    #+#             */
/*   Updated: 2017/05/09 01:12:45 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	get_nlink(t_data *data, nlink_t nlink, size_t size)
{
	char *tmp;

	tmp = ft_itoa(nlink);
	if (size < ft_strlen(tmp))
		size = ft_strlen(tmp);
	data->nlink = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}

/*
** getpwuid - search the password database for the given login
** name, user uid, or user uuid respectively, always returning the first
** one encountered.
*/

int	get_owner(t_data *data, uid_t uid, size_t size)
{
	char *tmp;
	struct passwd *pass;

	if ((pass = getpwuid(uid)) == NULL)
		tmp = ft_itoa(uid);
	else
		tmp = ft_strdup(pass->pw_name);
	if (size < ft_strlen(tmp))
		size = ft_strlen(tmp);
	data->uid = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}

/*
** struct group *getgrgid(gid_t gid);
** getgrgid  search the group database for the given group name pointed to by
** the group id given by gid, returning the first one encountered.
*/

int	get_group(t_data *data, gid_t git, size_t size)
{
	char *tmp;
	struct group *grp;

	if ((grp = getgrgid(git)) == NULL)
		tmp = ft_itoa(git);
	else
		tmp = ft_strdup(grp->gr_name);
	if (size < ft_strlen(tmp))
		size = ft_strlen(tmp);
	data->grp = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}

int	get_size(t_data *data, off_t s, size_t size)
{
	char *tmp;

	tmp = ft_itoa(s);
	if (size < ft_strlen(tmp))
		size = ft_strlen(tmp);
	data->size = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (size);
}

/*
** check total num
*/

size_t  	get_total(char *path, t_data *data, t_posib *option)
{
	struct stat	st;
	char		*tmp;

	tmp = ft_strjoin(path, data->name); // ./.DS_Store
	if (lstat(tmp, &st) == -1)
	{
		printf("Error lstat\n");
		return (0);
	}
	data->mode = check_permissions(st.st_mode);
	if (option->l)
	{
		option->size[0] = get_nlink(data, st.st_nlink, option->size[0]);
		option->size[1] = get_owner(data, st.st_uid, option->size[1]);
		option->size[2] = get_group(data, st.st_gid, option->size[2]);
		option->size[3] = get_size(data, st.st_size, option->size[3]);
	}
	free(tmp);
	if (data->name[0] != '.' || option->a)
		return (st.st_blocks);
	else
		return (0);
}
