/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 01:34:05 by kmurray           #+#    #+#             */
/*   Updated: 2017/05/09 01:41:24 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int stat_dir(char *path)
{
	struct stat str;

	if (stat(path, &str) == -1)
	{
		if (lstat(path, &str) == -1)
		{
		if (errno == ENOTDIR)
			return (0);
		//return create a function for errors
		}
	}
	if (S_ISDIR(str.st_mode))
		return (1);
	else if (S_ISLNK(str.st_mode))
		return (2);
	return (0);
}

t_data *read_directories(char *bpath, char *path,  t_posib *option, int *nb)
{
	int tmp = 0;
	DIR *dir;
	t_data *data = NULL;
	t_data *new = NULL;
	struct dirent *dp;

	//printf("path in read dir: %s\n", path);
	if ((dir = opendir(bpath)) == NULL)
	{
		/* ENOENT   No such file or directory		*/
		/* ENOTDIR  Not a directory			*/
		if(errno == ENOENT || errno == ENOTDIR)
		{
			if (stat_dir(path) != 0)
			{
				ft_putendl(ft_strsub(path, 2, ft_strlen(path)));
				return (NULL);
			}
		}
		printf("ERROR read directories\n");
		return (NULL);
	}

	//second part
	while ((dp = readdir(dir)) != NULL)
	{
		if ((new = (t_data*)malloc(sizeof(t_data))) == NULL)
			printf("Error allocating memory in read directories\n");
		init_elements(new);
		if ((new->name = ft_strdup(dp->d_name)) == NULL)
		{
			printf("new_element creating error\n");
			exit (1);
		}
		//get total number of blocks
		if ((tmp = get_total(bpath, new, option)) == -1)
			continue;
		option->total += tmp;
		printf("%s %s %s %s %s %s \n", new->mode, new->nlink, new->uid, new->grp, new->size, new->name);
		new = new->next;
		(*nb)++;
	}
	//need a fucntion to check for null directory
	(void)closedir(dir);
	return (data);

}
